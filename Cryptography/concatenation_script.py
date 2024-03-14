"""
File Concatenation Utility

This module provides utility functions for reading contents from files, concatenating strings with a delimiter, and writing content to a file.

Functions:
    read_file(file_path): Reads the contents of a file and returns them as bytes.
    concatenate_strings_with_delimiter(str1, str2, delimiter): Concatenates two strings with a delimiter.
    write_file(file_path, content): Writes content to a file.

Usage:
    To use this module, call the necessary functions with appropriate arguments. Ensure that you have the correct file paths and content set before calling the functions.

Example:
    encrypted_file_path = "encrypted.hex"
    digest_file_path = "Old_Digest.hex"

    encrypted_content = read_file(encrypted_file_path)
    digest_content = read_file(digest_file_path)

    concatenated_content = concatenate_strings_with_delimiter(encrypted_content, digest_content)

    output_file_path = "concatenated.hex"
    write_file(output_file_path, concatenated_content)

    print("Concatenated file is generated successfully.")
"""

import os

# Function to read contents from a file
def read_file(file_path):
    """
    Read the contents of a file and return them as bytes.

    Args:
        file_path (str): The path to the file to be read.

    Returns:
        bytes: The contents of the file.
    """
    with open(file_path, 'rb') as file:
        return file.read()

# Function to concatenate two strings with a delimiter
def concatenate_strings_with_delimiter(str1, str2, delimiter=b'//////////////////////the Digest: '):
    """
    Concatenate two strings with a delimiter.

    Args:
        str1 (bytes): The first string to be concatenated.
        str2 (bytes): The second string to be concatenated.
        delimiter (bytes, optional): The delimiter to be inserted between the strings. Default is b'//////////////////////the Digest: '.

    Returns:
        bytes: The concatenated string.
    """
    # Add delimiter after str1 and start the new line
    return str1 + b'\n' + delimiter + b'\n' + str2


# Function to write content to a file
def write_file(file_path, content):
    """
    Write content to a file.

    Args:
        file_path (str): The path to the file to be written.
        content (bytes): The content to be written to the file.
    """
    with open(file_path, 'wb') as file:
        file.write(content)

if __name__ == "__main__":
    encrypted_file_path = "encrypted.hex"
    digest_file_path = "Old_Digest.hex"

    encrypted_content = read_file(encrypted_file_path)
    digest_content = read_file(digest_file_path)

    concatenated_content = concatenate_strings_with_delimiter(encrypted_content, digest_content)

    output_file_path = "concatenated.hex"
    write_file(output_file_path, concatenated_content)

    print("Concatenated file is generated successfully.")
