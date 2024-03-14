"""
File Signature Generation

This module provides a function for generating a cryptographic signature for a file using HMAC-SHA256.

Functions:
    generate_signature(file_path, key): Generates a cryptographic signature for the given file using HMAC-SHA256.

Usage:
    To generate a signature for a file, call the 'generate_signature' function with the path to the file and the key.
    Ensure that you have the correct file path and key set before calling the function.

Example:
    if __name__ == "__main__":
        Old_Digest_path = 'Old_Digest.hex'
        Hex_file_path = 'App.hex'
        key = b'fed9ee8054a841b74f99d5364c6349944e9a323905afc314d04c4d1a74332ae0'

        Old_Digest_generated_hash = generate_signature(Hex_file_path, key)

        with open(Old_Digest_path, 'wb') as hash_file:
            hash_file.write(Old_Digest_generated_hash)

        print("Signature generated and saved to pre_generated_hash.hex")
        print("Digest:", Old_Digest_generated_hash.hex())
"""

import hashlib
import hmac

def generate_signature(file_path, key):
    """
    Generate a cryptographic signature for a file using HMAC-SHA256.

    Args:
        file_path (str): The path to the file for which the signature will be generated.
        key (bytes): The secret key used for the HMAC operation.

    Returns:
        bytes: The cryptographic signature of the file.

    """
    with open(file_path, 'rb') as file:
        file_content = file.read()
    digest = hmac.new(key, file_content, hashlib.sha256).digest()
    return digest

if __name__ == "__main__":
    Old_Digest_path = 'Old_Digest.hex'
    Hex_file_path = 'App.hex'
    key = b'fed9ee8054a841b74f99d5364c6349944e9a323905afc314d04c4d1a74332ae0' 
    Old_Digest_generated_hash = generate_signature(Hex_file_path, key)

    with open(Old_Digest_path, 'wb') as hash_file:
        hash_file.write(Old_Digest_generated_hash)

    print("Signature generated and saved to pre_generated_hash.hex")
    print("Digest:", Old_Digest_generated_hash.hex())
