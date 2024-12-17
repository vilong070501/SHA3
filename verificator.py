import hashlib

def compute_sha3_256(file_path):
    # Créer un objet hash SHA3-256
    sha3_hash = hashlib.sha3_256()

    # Ouvrir le fichier en mode binaire
    with open(file_path, 'rb') as file:
        # Lire le fichier par petits morceaux
        while chunk := file.read(8192):  # Lire 8192 octets à la fois
            sha3_hash.update(chunk)  # Mettre à jour le hachage avec ce bloc

    # Retourner le hash sous forme hexadécimale
    return sha3_hash.hexdigest()

# Exemple d'utilisation
file_path = 'text.txt'  # Remplace par le chemin vers ton fichier
hash_value = compute_sha3_256(file_path)

print(f'SHA3-256 Hash obtenu: {hash_value}')
