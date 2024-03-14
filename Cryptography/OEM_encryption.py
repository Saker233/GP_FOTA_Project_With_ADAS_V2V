"""
RSA Encryption Implementation

This module provides functions for RSA encryption, including primality testing, modular
inverse calculation, and file encryption.

Functions:
    is_prime(number): Checks if a number is prime.
    mod_inverse(e, phi): Calculates the modular inverse of 'e' modulo 'phi'.
    encrypt_file(file_path, e, n): Encrypts a file using RSA encryption and writes the
                                   encrypted content to a file.

Usage:
    To use this module, simply call the 'encrypt_file' function with the appropriate
    arguments. Ensure that you have the public key 'e', private key 'd', and modulus 'n'
    set correctly before calling the function.

Example:
    if __name__ == "__main__":
        # Fixed values for public key, private key, and modulus
        e = 3219677  # Fixed public key
        d = 2109953  # Fixed private key
        n = 3299453  # Fixed modulus

        encrypt_file('App.hex', e, n)
"""

import math

def is_prime(number):
    """
    Check if a number is prime.

    Args:
        number (int): The number to be tested.

    Returns:
        bool: True if the number is prime, False otherwise.
    """
    if number < 2:
        return False
    for i in range(2, number // 2 + 1):
        if number % i == 0:
            return False
    return True

def mod_inverse(e, phi):
    """
    Calculate the modular inverse of 'e' modulo 'phi'.

    Args:
        e (int): The number for which to find the modular inverse.
        phi (int): The modulus.

    Returns:
        int: The modular inverse of 'e' modulo 'phi'.

    Raises:
        ValueError: If the modular inverse does not exist.
    """
    for d in range(3, phi):
        if (d * e) % phi == 1:
            return d
    raise ValueError("mod_inverse does not exist")

def encrypt_file(file_path, e, n):
    """
    Encrypt a file using RSA encryption and write the encrypted content to a file.

    Args:
        file_path (str): The path to the file to be encrypted.
        e (int): The public key.
        n (int): The modulus.

    Writes:
        The encrypted content to a file named 'encrypted.hex'.
    """
    with open(file_path, 'rb') as file:
        file_content = file.read()
    ciphertext = [pow(byte, e, n) for byte in file_content]
    with open('encrypted.hex', 'w') as encrypted_file:
        for byte in ciphertext:
            encrypted_file.write(format(byte, 'x').zfill(4) + '\n')  # Fixed length of 4 hexadecimal characters

if __name__ == "__main__":
    # Fixed values for public key, private key, and modulus
    e = 3219677  # Fixed public key
    d = 2109953  # Fixed private key
    n = 3299453  # Fixed modulus

    encrypt_file('App.hex', e, n)
