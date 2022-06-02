#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <conio.h>

#include <podofo.h>


namespace pdf = PoDoFo;

void writePDF(pdf::PdfMemDocument& file, const std::string& outputPath) {
	file.Write(outputPath.c_str());
}

void merge(pdf::PdfMemDocument& base, std::string mergeFile)
{
	pdf::PdfMemDocument merge(mergeFile.c_str());

	base.Append(merge);
}

void iterFiles(const std::string& inputPath, std::string& outputPath)
{
	outputPath += "/merged.pdf";
	pdf::PdfMemDocument base = pdf::PdfMemDocument();
	std::string filename;
	bool noPdfsFlag = true;
	for (std::filesystem::path file : std::filesystem::directory_iterator(inputPath)) {
		// Get string of filename:
		filename = file.generic_string();
		// Check that file is pdf:
		size_t start_pos = filename.find(".pdf");
		if (start_pos == std::string::npos)
			std::cerr << filename << " is not a pdf file.\n";
		else {
			noPdfsFlag = false;
			merge(base, filename);
			writePDF(base, outputPath);
		}

		if (noPdfsFlag) {
			std::cout << "No PDFs found in the following directory:\n" << inputPath << "\n";
		}
	}
}

void savePaths(const std::string& inputPath, const std::string& outputPath)
{
	std::cout << "\n'pdf_merge_paths.txt' will be created in the current working directory.\n"
		<< "This file will be used in the future to automatically set the paths.\n";
	std::ofstream outData{ "pdf_merge_paths.txt" };
	outData << inputPath << "\n";
	outData << outputPath;
}

void getPaths(std::string& inputPath, std::string& outputPath)
{
	std::cout << "\n'pdf_merge_paths.txt' not found.\n\n"
		<< "You will be asked to enter two paths : an input path\n"
		<< "(the location of the PDFs to be merged) and an output\n"
		<< "path (the location to store the merged PDF). These\n"
		<< "directories will be reused the next time the program runs.\n"
		<< "To set a new path, delete the 'pdf_merge_paths.txt' file.\n\n"
		<< "(Use forward slash, /, to separate path parts.)\n"
		<< "Input path: ";
	std::cin >> inputPath;

	std::cout << "Output path: ";
	std::cin >> outputPath;
}

int main()
{
	bool run = true;
	do {
		std::string inputPath;
		std::string outputPath;
		std::ifstream inData{ "pdf_merge_paths.txt" };

		std::cout << "NOTE:\nIn order for the program to merge PDFs in the right order,\n"
			<< "their filenames should begin with an ordered sequence. E.g.,\n"
			<< "'1 file.pdf', '2 file.pdf' etc...\n\n"
			<< "Press any key to continue ";

		while (!_kbhit()) {};
		_getch();


		if (!inData.good()) {
			getPaths(inputPath, outputPath);
			savePaths(inputPath, outputPath);
		}
		else {
			inData >> inputPath;
			inData >> outputPath;
		}

		iterFiles(inputPath, outputPath);

		// Run again option:
		char cont;
		std::cout << "\nRun again? (y/n)\n";
		std::cin >> cont;
		while (std::tolower(cont) != 'y' && std::tolower(cont) != 'n') {
			std::cout << "Please select 'y' or 'n': ";
			std::cin >> cont;
		}
		if (std::tolower(cont) == 'n')
			run = false;
		std::cout << std::endl;
	} while (run);

	return 0;
}
