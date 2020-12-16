// ReadStdfTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <string.h> // for strcpy()
#include <chrono>

#include "stdf_v4_file.h"

#define STDF_V4_RECORD_COUNT 25

using namespace std;

STDF_FILE_ERROR read_std_file(const string& filename, STDF_FILE* stdf_file);

STDF_FILE_ERROR write_to_txt(const string& filename, STDF_FILE* stdf_file);

void check_status(STDF_FILE_ERROR e);

int main(int argc, char** argv) {

    string file1("C:\\Users\\ITadmin\\Desktop\\Test\\C\\ReadStdfTest\\ReadStdfTest\\ReadStdfTest\\test_big.std");
    string file2("C:\\Users\\ITadmin\\Desktop\\Test\\C\\ReadStdfTest\\ReadStdfTest\\ReadStdfTest\\test_big.txt");

    try {
        /*if (argc != 3) {
            throw runtime_error("Std file or text file path not specified");
        }*/

        //tring stdf_file_name(argv[1]);
        //string txt_file_path(argv[2]);

        string stdf_file_name(file1.c_str());
        string txt_file_path(file2.c_str());

        STDF_FILE* stdf_file = new STDF_FILE();

        cout << "Read Stdf ";
        auto start_time = std::chrono::steady_clock::now();
        check_status(read_std_file(stdf_file_name, stdf_file));
        auto end_time = std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsed_second = end_time - start_time;

        cout << "Read std file elapsed time: " << elapsed_second.count() << endl;

        cout << "Write to txt file ";
        check_status(write_to_txt(txt_file_path, stdf_file));

    }
    catch (runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}

STDF_FILE_ERROR read_std_file(const string& filename, STDF_FILE* stdf_file) {
    return stdf_file->read(filename.c_str());
}

STDF_FILE_ERROR write_to_txt(const string& filename, STDF_FILE* stdf_file) {
    return stdf_file->write(filename.c_str());
}

void check_status(STDF_FILE_ERROR e) {
    switch (e) {
    case STDF_FILE_ERROR::STDF_OPERATE_OK:
        cout << "Operation success" << endl;
        break;
    case STDF_FILE_ERROR::READ_ERROR:
        throw runtime_error("Read error");
        break;
    case STDF_FILE_ERROR::WRITE_ERROR:
        throw runtime_error("Write error");
        break;
    default:
        throw runtime_error("Other error");
    }
}