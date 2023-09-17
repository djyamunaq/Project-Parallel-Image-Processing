#include <iostream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include <opencv2/opencv.hpp>

using std::cout;
using std::cin;
using std::endl;

// Function to process a segment of the image
void processImageSegment(cv::Mat& input, cv::Mat& output, int startRow, int endRow) {
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < input.cols; ++j) {
            output.at<float>(i, j) = 1000*input.at<float>(i, j); 
        }
    }
}

int main(int argc, char** argv) {
    // Set default num of threads to 1
    int numThreads = 1;
    // Check if num of threads were provided in command line
    if (argc > 1) {
        numThreads = atoi(argv[1]);

        if (numThreads <= 0) {
            cout << "Invalid number of threads" << endl;
            return 1;
        }

        cout << "Number of threads: " << numThreads << endl;
    }

    // Load the input image
    cv::Mat inputImage = cv::imread("../data/input.jpg");
    // Check if there is a valid image
    if (inputImage.empty()) {
        cout << "Image invalid/No image provided. Exiting program..." << endl;
        return 1;
    }

    // Create an output image with the same dimensions as the input
    cv::Mat outputImage(inputImage.rows, inputImage.cols, inputImage.type());

    // Calculate the number of rows each thread will process
    int rowsPerThread = inputImage.rows / numThreads;

    // Vector to store thread objects
    std::vector<std::thread> threads;

    // Launch threads for parallel processing
    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? inputImage.rows : (i + 1) * rowsPerThread; // Check if is last row

        threads.emplace_back(processImageSegment, std::ref(inputImage), std::ref(outputImage), startRow, endRow);
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }

    // Save the processed image.
    cv::imwrite("../data/output.jpg", outputImage);

    // Show the processed image
    cv::imshow("Processed Image", outputImage);
    cv::waitKey(0);

    return 0;
}
