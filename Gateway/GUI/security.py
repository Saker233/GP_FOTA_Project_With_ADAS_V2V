import os
import hmac
import hashlib

def separate_concatenated_file(concatenated_file_path):
    with open(concatenated_file_path, 'rb') as file:
        content = file.read()
        file.close()
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
    with open(file_path, 'rb') as file:
        file_content = file.readlines()
    plaintext = [pow(int(byte.strip(), 16), d, n) for byte in file_content]
    with open('decrypted.hex', 'wb') as decrypted_file:
        decrypted_file.write(bytes(plaintext))

def generate_signature(file_path, key):
    with open(file_path, 'rb') as file:
        file_content = file.read()
    # key_bytes = key.encode('utf-8')  # Encode key string as bytes      
    digest = hmac.new(key, file_content, hashlib.sha256).digest()
    return digest

def verify_signature(Old_Digest_generated_hash_path, New_Digest_generated_hash_path):
    with open(Old_Digest_generated_hash_path, 'rb') as Old_Digest_generated_hash_file:
        Old_Digest_generated_hash = Old_Digest_generated_hash_file.read()

    with open(New_Digest_generated_hash_path, 'rb') as New_Digest_generated_hash_file:
        New_Digest_generated_hash = New_Digest_generated_hash_file.read()

    return Old_Digest_generated_hash == New_Digest_generated_hash

def cleanup(filenames: list):
    directory = os.getcwd()  # Get the current directory
    files = os.listdir(directory)  # List all files in the directory

    # Filter out hex files except the one with the specific name
    for file in files: 
        if file.find("file") > -1:
            filenames.append(file)
    hex_files = [file for file in files if file.endswith('.hex') and file not in filenames]

    # Remove each hex file
    for hex_file in hex_files:
        os.remove(os.path.join(directory, hex_file))
        print(f"Removed: {hex_file}")

def decryption_process(concatenated_file_path):
    return_state = False
    # Step 1: Separate concatenated file into encrypted and digest
    # concatenated_file_path = "file4_40_00_00.hex"
    separate_concatenated_file(concatenated_file_path)

    # Step 2: Decrypt the encrypted file
    d = 2109953 #os.environ.get('d')
    n = 3299453 #os.environ.get('n')
    if d is None or n is None:
        print("Error: Values for d and/or n are missing from environment variables.")
    else:
        d = int(d)
        n = int(n)
        decrypt_file('encrypted2.hex', d, n)

    # Step 3: Generate signature for decrypted file
    key = b'fed9ee8054a841b74f99d5364c6349944e9a323905afc314d04c4d1a74332ae0'
#os.environ.get('key')
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
        with open(concatenated_file_path, 'wb') as verified_decrypted_file:
            with open('decrypted.hex', 'rb') as decrypted_file:
                verified_decrypted_file.write(decrypted_file.read())
        print("Decrypted file saved as verified_decrypted.hex")
        return_state = True
    else:
        print("Signature verific/ation failed. The file has been tampered with.")
        return_state = False
    
    cleanup(["verified_decrypted.hex", "App.hex"])
    return return_state
