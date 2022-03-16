/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "UtilitiesTests.h"
#include <Ishiko/FileSystem/FileSystemErrorCategory.hpp>
#include <Ishiko/FileSystem/Utilities.hpp>
#include <boost/filesystem/operations.hpp>

using namespace Ishiko;
using namespace Ishiko::FileSystem;
using namespace Ishiko::Tests;

UtilitiesTests::UtilitiesTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Utilities tests", context)
{
    append<HeapAllocationErrorsTest>("Exists test 1", ExistsTest1);
    append<HeapAllocationErrorsTest>("Exists test 2", ExistsTest2);
    append<HeapAllocationErrorsTest>("Exists test 3", ExistsTest3);
    append<HeapAllocationErrorsTest>("GetFileSize test 1", GetFileSizeTest1);
    append<HeapAllocationErrorsTest>("GetFileSize test 2", GetFileSizeTest2);
    append<HeapAllocationErrorsTest>("IsDirectory test 1", IsDirectoryTest1);
    append<HeapAllocationErrorsTest>("IsDirectory test 2", IsDirectoryTest2);
    append<HeapAllocationErrorsTest>("IsDirectory test 3", IsDirectoryTest3);
    append<HeapAllocationErrorsTest>("IsEmpty test 1", IsEmptyTest1);
    append<HeapAllocationErrorsTest>("IsEmpty test 2", IsEmptyTest2);
    append<HeapAllocationErrorsTest>("IsEmpty test 3", IsEmptyTest3);
    append<HeapAllocationErrorsTest>("IsEmpty test 4", IsEmptyTest4);
    append<HeapAllocationErrorsTest>("IsEmpty test 5", IsEmptyTest5);
    append<HeapAllocationErrorsTest>("ToAbsolutePath test 1", ToAbsolutePathTest1);
    append<HeapAllocationErrorsTest>("ToAbsolutePath test 2", ToAbsolutePathTest2);
    append<HeapAllocationErrorsTest>("CreateEmptyFile test 1", CreateEmptyFileTest1);
    append<HeapAllocationErrorsTest>("CreateEmptyFile test 2", CreateEmptyFileTest2);
    append<HeapAllocationErrorsTest>("ReadFile test 1", ReadFileTest1);
    append<HeapAllocationErrorsTest>("ReadFile test 2", ReadFileTest2);
    append<HeapAllocationErrorsTest>("ReadFile test 3", ReadFileTest3);
    append<HeapAllocationErrorsTest>("ReadFile test 4", ReadFileTest4);
    append<HeapAllocationErrorsTest>("ReadFile test 5", ReadFileTest5);
    append<HeapAllocationErrorsTest>("ReadFile test 6", ReadFileTest6);
    append<HeapAllocationErrorsTest>("ReadFile test 7", ReadFileTest7);
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
    append<HeapAllocationErrorsTest>("GetVolumeList test 1", GetVolumeListTest1);
#endif
}

void UtilitiesTests::ExistsTest1(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("doesnotexist"));

    ISHIKO_FAIL_IF(Exists(inputPath.string().c_str()));
    ISHIKO_PASS();
}

void UtilitiesTests::ExistsTest2(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("file1.txt"));

    ISHIKO_FAIL_IF_NOT(Exists(inputPath.string().c_str()));
    ISHIKO_PASS();
}

void UtilitiesTests::ExistsTest3(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory());

    ISHIKO_FAIL_IF_NOT(Exists(inputPath.string().c_str()));
    ISHIKO_PASS();
}

void UtilitiesTests::GetFileSizeTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("file1.txt"));

    Error error;
    size_t fileSize = GetFileSize(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(fileSize, 5);
    ISHIKO_PASS();
}

void UtilitiesTests::GetFileSizeTest2(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("doesnotexist"));

    Error error;
    size_t fileSize = GetFileSize(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(error.condition(), FileSystemErrorCategory::Value::notFound);
    ISHIKO_FAIL_IF_NEQ(fileSize, 0);
    ISHIKO_PASS();
}

void UtilitiesTests::IsDirectoryTest1(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory());

    Error error;
    bool isDir = IsDirectory(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NOT(isDir);
    ISHIKO_PASS();
}

void UtilitiesTests::IsDirectoryTest2(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("file1.txt"));

    Error error;
    bool isDir = IsDirectory(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF(isDir);
    ISHIKO_PASS();
}

void UtilitiesTests::IsDirectoryTest3(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("doesnotexist"));

    Error error;
    bool isDir = IsDirectory(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(error.condition(), FileSystemErrorCategory::Value::notFound);
    ISHIKO_FAIL_IF(isDir);
    ISHIKO_PASS();
}

void UtilitiesTests::IsEmptyTest1(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("empty.txt"));

    Error error;
    bool empty = IsEmpty(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NOT(empty);
    ISHIKO_PASS();
}

void UtilitiesTests::IsEmptyTest2(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("file1.txt"));

    Error error;
    bool empty = IsEmpty(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF(empty);
    ISHIKO_PASS();
}

void UtilitiesTests::IsEmptyTest3(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestOutputPath("empty"));
    boost::filesystem::create_directory(inputPath);

    Ishiko::Error error;
    bool empty = IsEmpty(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NOT(empty);
    ISHIKO_PASS();
}

void UtilitiesTests::IsEmptyTest4(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory());

    Ishiko::Error error;
    bool empty = IsEmpty(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF(empty);
    ISHIKO_PASS();
}

void UtilitiesTests::IsEmptyTest5(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("doesnotexist"));

    Ishiko::Error error;
    bool empty = IsEmpty(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(error.condition(), FileSystemErrorCategory::Value::notFound);
    ISHIKO_FAIL_IF(empty);
    ISHIKO_PASS();
}

void UtilitiesTests::ToAbsolutePathTest1(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("doesnotexist"));

    std::string currentPath = boost::filesystem::current_path().string();
#ifdef WIN32
    currentPath += "\\";
#else
    currentPath += "/";
#endif
    
    std::string absolutePath;
    ToAbsolutePath(inputPath.string().c_str(), absolutePath);

    ISHIKO_FAIL_IF_NEQ(absolutePath, currentPath + inputPath.string());
    ISHIKO_PASS();
}

void UtilitiesTests::ToAbsolutePathTest2(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("doesnotexist"));

    std::string currentPath = boost::filesystem::current_path().string();
#ifdef WIN32
    currentPath += "\\";
#else
    currentPath += "/";
#endif

    std::string absolutePath;
    ToAbsolutePath(inputPath.string(), absolutePath);

    ISHIKO_FAIL_IF_NEQ(absolutePath, currentPath + inputPath.string());
    ISHIKO_PASS();
}

void UtilitiesTests::CreateEmptyFileTest1(Test& test)
{
    boost::filesystem::path outputPath = test.context().getTestOutputPath("file1.txt");

    Ishiko::Error error;
    CreateEmptyFile(outputPath, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NOT(Exists(outputPath));
    ISHIKO_PASS();
}

void UtilitiesTests::CreateEmptyFileTest2(Test& test)
{
    boost::filesystem::path outputPath = test.context().getTestOutputPath("file2.txt");

    Error error;
    CreateEmptyFile(outputPath, error);

    ISHIKO_ABORT_IF(error);
    
    CreateEmptyFile(outputPath, error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(error.condition(), FileSystemErrorCategory::Value::alreadyExists);
    ISHIKO_PASS();
}

void UtilitiesTests::ReadFileTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("file1.txt"));

    Error error;
    const int bufferSize = 10;
    char buffer[bufferSize];
    size_t bytesRead = ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(bytesRead, 5);
    ISHIKO_PASS();
}

void UtilitiesTests::ReadFileTest2(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("doesnotexist"));

    Error error;
    const int bufferSize = 10;
    char buffer[bufferSize];
    size_t bytesRead = ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(bytesRead, 0);
    ISHIKO_PASS();
}

void UtilitiesTests::ReadFileTest3(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("file1.txt"));

    Error error;
    const int bufferSize = 2;
    char buffer[bufferSize];
    size_t bytesRead = ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(error.condition(), FileSystemErrorCategory::Value::bufferOverflow);
    ISHIKO_FAIL_IF_NEQ(bytesRead, 5);
    ISHIKO_PASS();
}

void UtilitiesTests::ReadFileTest4(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("file1.txt"));

    Error error;
    std::string bytes = ReadFile(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(bytes, "hello");
    ISHIKO_PASS();
}

void UtilitiesTests::ReadFileTest5(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("doesnotexist"));

    Error error;
    std::string bytes = ReadFile(inputPath.string().c_str(), error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(bytes, "");
    ISHIKO_PASS();
}

void UtilitiesTests::ReadFileTest6(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("file1.txt"));

    Error error;
    std::string bytes = ReadFile(inputPath, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(bytes, "hello");
    ISHIKO_PASS();
}

void UtilitiesTests::ReadFileTest7(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataPath("doesnotexist"));

    Error error;
    std::string bytes = ReadFile(inputPath, error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(bytes, "");
    ISHIKO_PASS();
}

#if ISHIKO_OS == ISHIKO_OS_WINDOWS
void UtilitiesTests::GetVolumeListTest1(Ishiko::Tests::Test& test)
{
    Ishiko::Error error;
    std::vector<std::string> volumeNames;
    GetVolumeList(volumeNames, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_ABORT_IF_NOT(volumeNames.size() >= 1);

    for (const std::string& volumeName : volumeNames)
    {
        DWORD volumePathNamesLength = 5 * (MAX_PATH + 1) + 1;
        char* volumePathNames = new char[volumePathNamesLength];
        if (GetVolumePathNamesForVolumeNameA(volumeName.c_str(), volumePathNames, volumePathNamesLength,
            &volumePathNamesLength))
        {
            if ((volumePathNamesLength != 0) && (volumePathNames[0] != 0) && (strcmp(volumePathNames, "C:\\") == 0))
            {
                ISHIKO_PASS();
            }
        }
        delete[] volumePathNames;
    }
}
#endif
