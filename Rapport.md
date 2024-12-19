# Rapport sur l'implémentation de la famille SHA3 Keccak

## Auteurs

- LUONG Vi Long <<vi-long.luong@epita.fr>>
- SAMBIANI Uriel <<uriel.sambiani@epita.fr>>

## Références

- [Wikipedia](https://en.wikipedia.org/wiki/SHA-3)
- [Keccak Team](https://keccak.team/)

## Utilisation du programme

### Prérequis

- Make outil

```bash
make && ./sha3
```

Fournir le fichier à chiffre
```
Path to the file to hash:
```

Choisir la famille de SHA3
```
SHA3 family (224, 256, 384, 512):
```

## Résultats obtenus

- **Précision des résultats** : L'implémentation des 4 familles de SHA3 (224, 256, 384, 512) donne des résultats identiques à ceux générés par OpenSSL et les outils de hachage en ligne (par exemple, [SHA3-256 en ligne](https://emn178.github.io/online-tools/sha3_256.html)).

- **Performance** : L'implémentation est capable de traiter des fichiers texte ou binaires de taille relativement grande (environ 60 Mo) en 5 à 6 secondes.

## Points intéressants

### Gestion de la mémoire
- L'utilisation des structures de données comme `std::array` et `std::vector` garantit une gestion efficace et sécurisée de la mémoire.
- Le choix de `std::array` pour le `hash_buffer` permet une manipulation rapide des données tout en minimisant les risques de débordement de mémoire.

### Optimisation des opérations
Lors de l'étape d'absorption, le traitement des données est effectué bloc par bloc, en combinant directement les octets du message dans les lignes du tableau d'état à l'aide d'opérations bitwise.

## Défis rencontrés
- Assurer la conformité des opérations bitwise avec les spécifications Keccak pour éviter les décalages incorrects.
- La gestion de fichiers de grande taille a nécessité des tests approfondis.

