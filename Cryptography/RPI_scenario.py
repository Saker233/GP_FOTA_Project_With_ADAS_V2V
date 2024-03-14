"""
File Processing Utility

This module provides utility functions for separating concatenated files, decrypting files, generating signatures, verifying signatures, and cleaning up files.

Functions:
    separate_concatenated_file(concatenated_file_path): Separates a concatenated file into encrypted and digest parts.
    decrypt_file(file_path, d, n): Decrypts a file using RSA encryption.
    generate_signature(file_path, key): Generates a cryptographic signature for a file using HMAC-SHA256.
    verify_signature(Old_Digest_generated_hash_path, New_Digest_generated_hash_path): Verifies the integrity of a file by comparing two cryptographic signatures.
    clean_up(): Cleans up generated files except for specified ones.

Usage:
    To use this module, call the functions sequentially in the provided order. Ensure that you have the correct file paths, keys, and environment variables set before calling the functions.

Example:
    # Step 1: Separate concatenated file into encrypted and digest
    concatenated_file_path = "concatenated.hex"
    separate_concatenated_file(concatenated_file_path)

    # Step 2: Decrypt the encrypted file
    d = os.environ.get('d')
    n = os.environ.get('n')
    decrypt_file('encrypted2.hex', d, n)

    # Step 3: Generate signature for decrypted file
    key = os.environ.get('key')
    New_Digest_path = 'New_Digest.hex'
    Hex_file_path = 'decrypted.hex'
    New_Digest_generated_hash = generate_signature(Hex_file_path, key)

    # Step 4: Verify signature
    Old_Digest_path = 'digest2.hex'
    verification_result = verify_signature(Old_Digest_path, New_Digest_path)

    # Clean up generated files
    clean_up()
"""

import os
import hmac
import hashlib

def separate_concatenated_file(concatenated_file_path):
    """
    Separates a concatenated file into encrypted and digest parts.

    Args:
        concatenated_file_path (str): The path to the concatenated file.
    """
    with open(concatenated_file_path, 'rb') as file:
        content = file.read()
    # Split the content at the delimiter
    parts = content.split(b'//////////////////////the Digest: ')
    if len(parts) != 2:
        print("Delimiter not found in the concatenated file.")
        return
    # Extract encrypted content and digest content
    encrypted_content, digest_content = parts
    # Write the encrypted content to a file
    with open('encrypted2.hex', 'wb') as encrypted_file:
        encrypted_file.write(encrypted_content.strip())
    # Write the digest content to a file
    with open('digest2.hex', 'wb') as digest_file:
        digest_file.write(digest_content.strip())

def decrypt_file(file_path, d, n):
    """
    Decrypts a file using RSA encryption.

    Args:
        file_path (str): The path to the file to be decrypted.
        d (int): The private key for decryption.
        n (int): The modulus used for decryption.
    """
    with open(file_path, 'rb') as file:
        file_content = file.readlines()
    plaintext = [pow(int(byte.strip(), 16), d, n) for byte in file_content]
    with open('decrypted.hex', 'wb') as decrypted_file:
        decrypted_file.write(bytes(plaintext))

def generate_signature(file_path, key):
    """
    Generates a cryptographic signature for a file using HMAC-SHA256.

    Args:
        file_path (str): The path to the file for which the signature will be generated.
        key (str): The secret key used for the HMAC operation.

    Returns:
        bytes: The cryptographic signature of the file.
    """
    with open(file_path, 'rb') as file:
        file_content = file.read()
    key_bytes = key.encode('utf-8')  # Encode key string as bytes      
    digest = hmac.new(key_bytes, file_content, hashlib.sha256).digest()
    return digest

def verify_signature(Old_Digest_generated_hash_path, New_Digest_generated_hash_path):
    """
    Verifies the integrity of a file by comparing two cryptographic signatures.

    Args:
        Old_Digest_generated_hash_path (str): The path to the old digest file.
        New_Digest_generated_hash_path (str): The path to the new digest file.

    Returns:
        bool: True if the signatures match, False otherwise.
    """
    with open(Old_Digest_generated_hash_path, 'rb') as Old_Digest_generated_hash_file:
        Old_Digest_generated_hash = Old_Digest_generated_hash_file.read()

    with open(New_Digest_generated_hash_path, 'rb') as New_Digest_generated_hash_file:
        New_Digest_generated_hash = New_Digest_generated_hash_file.read()

    return Old_Digest_generated_hash == New_Digest_generated_hash

def clean_up():
    """
    Cleans up generated files except for specified ones.
    """
    # List of files to keep
    keep_files = ['App.hex', 'concatenated.hex', 'verified_decrypted.hex']

    # Get a list of all .hex files in the directory
    files = [f for f in os.listdir() if f.endswith('.hex')]

    # Remove files that are not in the list of files to keep
    for file in files:
        if file not in keep_files:
            os.remove(file)

if __name__ == "__main__":
    # Step 1: Separate concatenated file into encrypted and digest
    concatenated_file_path = "concatenated.hex"
    separate_concatenated_file(concatenated_file_path)

    # Step 2: Decrypt the encrypted file
    d = os.environ.get('d')
    n = os.environ.get('n')
    if d is None or n is None:
        print("Error: Values for d and/or n are missing from environment variables.")
    else:
        d = int(d)
        n = int(n)
        decrypt_file('encrypted2.hex', d, n)

    # Step 3: Generate signature for decrypted file
    key = os.environ.get('key')
    if key is None:
        print("Error: Value for key is missing from environment variables.")
    else:
        New_Digest_path = 'New_Digest.hex'
        Hex_file_path = 'decrypted.hex'
        New_Digest_generated_hash = generate_signature(Hex_file_path, key)
        with open(New_Digest_path, 'wb') as hash_file:
            hash_file.write(New_Digest_generated_hash)
        print("Signature generated and saved to New_Digest.hex")
        print("Digest:", New_Digest_generated_hash.hex())

    # Step 4: Verify signature
    Old_Digest_path = 'digest2.hex'
    verification_result = verify_signature(Old_Digest_path, New_Digest_path)
    if verification_result:
        print("Signature verification successful. The file has not been tampered with.")
        # Save decrypted file externally
        with open('verified_decrypted.hex', 'wb') as verified_decrypted_file:
            with open('decrypted.hex', 'rb') as decrypted_file:
                verified_decrypted_file.write(decrypted_file.read())
        print("Decrypted file saved as verified_decrypted.hex")
    else:
        print("Signature verification failed. The file has been tampered with.")

    #
