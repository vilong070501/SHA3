import hashlib

def compute_sha3_224(file_path):
    sha3_hash = hashlib.sha3_224()

    with open(file_path, 'rb') as file:
        while chunk := file.read(8192):
            sha3_hash.update(chunk)

    return sha3_hash.hexdigest()

def compute_sha3_256(file_path):
    sha3_hash = hashlib.sha3_256()

    with open(file_path, 'rb') as file:
        while chunk := file.read(8192):
            sha3_hash.update(chunk)

    return sha3_hash.hexdigest()

def compute_sha3_384(file_path):
    sha3_hash = hashlib.sha3_384()

    with open(file_path, 'rb') as file:
        while chunk := file.read(8192):
            sha3_hash.update(chunk)

    return sha3_hash.hexdigest()

def compute_sha3_512(file_path):
    sha3_hash = hashlib.sha3_512()

    with open(file_path, 'rb') as file:
        while chunk := file.read(8192):
            sha3_hash.update(chunk)

    return sha3_hash.hexdigest()

file_path = input("Filepath: ")

hash_value = compute_sha3_224(file_path)
print(f'SHA3-224 Hash: {hash_value}')

hash_value = compute_sha3_256(file_path)
print(f'SHA3-256 Hash: {hash_value}')

hash_value = compute_sha3_384(file_path)
print(f'SHA3-384 Hash: {hash_value}')

hash_value = compute_sha3_512(file_path)
print(f'SHA3-512 Hash: {hash_value}')
