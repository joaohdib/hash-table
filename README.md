# hash-table
# Hashing Algorithm for License Plate Management

This project is a college assignment that implements a hashing algorithm in C. The program manages vehicle license plates using a hash table with collision handling. The hash table is designed to store license plates in the format "CCCNNNN," where `C` is an uppercase letter and `N` is a numeral.

## Features

- **Hash Table Implementation**: Uses open addressing with quadratic probing for collision resolution.
- **Operations**:
  - **Insertion**: Inserts license plates into the hash table.
  - **Search**: Searches for license plates in the hash table.
  - **Deletion**: Deletes license plates from the hash table.
- **Collision Tracking**: Tracks and prints the number of collisions encountered during insertion.

## Files

- `main.c`: Contains the implementation of the hashing algorithm and the main program logic.
- `placas.txt`: Input file containing license plates to be processed. Ensure this file is present in the same directory as the executable.

## Compilation

To compile the program, use the following command:

``` gcc -o hash_table main.c ```

## Usage

1. **Prepare the Input File**: Ensure `placas.txt` is in the same directory as the executable. The file should contain one license plate per line.
2. **Run the Program**:

``` ./hash_table ```

3. **Output**: The program will display the time taken for insertion, search, and deletion operations, along with the total number of collisions.

## Example Output

```
--- INSERINDO PLACA ---

TEMPO DO INSERT: 0.002345

--- BUSCANDO PLACA ---

TEMPO DA BUSCA: 0.001234

--- DELETANDO PLACA: ---

TEMPO DO DELETE: 0.003456

--- QTD COLISOES: 123 ---

```

## Functions

- **`int calculaHash(char* placa)`**: Computes the hash value for a given license plate.
- **`void insereHashTable(Placa* placa, char* HashTable[], int hash, int* qtdColisoes)`**: Inserts a license plate into the hash table and handles collisions.
- **`void printaColisoes(int* qtdColisoes)`**: Prints the number of collisions encountered.
- **`int procuraColisao(char* placa, char* hashTable[])`**: Searches for collisions in the hash table.
- **`int procuraHashTable(char* placa, char* hashTable[])`**: Searches for a license plate in the hash table.
- **`void deleteHashTable(char* placa, char* hashTable[])`**: Deletes a license plate from the hash table.

## Notes

- The hash table size is set to 1031, which is a prime number larger than 1024.
- The program uses quadratic probing for collision resolution.
