#include <stdio.h>

// Structure to represent a memory block
struct Block {
    int block_no;
    int block_size;
    int is_free; // 1 = free, 0 = occupied
};

// Structure to represent a file
struct File {
    int file_no;
    int file_size;
};

// First Fit memory allocation function
void firstFit(struct Block blocks[], int n_blocks, struct File files[], int n_files) {
    printf("\nMemory Management Scheme - First Fit\n");
    printf("File_no\tFile_size\tBlock_no\tBlock_size\tFragment\n");

    for (int i = 0; i < n_files; i++) {
        int allocated = 0;

        // Allocate the first available block that fits the file
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j].is_free && blocks[j].block_size >= files[i].file_size) {
                int fragment = blocks[j].block_size - files[i].file_size;
                blocks[j].is_free = 0;

                printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
                       files[i].file_no,
                       files[i].file_size,
                       blocks[j].block_no,
                       blocks[j].block_size,
                       fragment);

                allocated = 1;
                break; // Stop after first suitable block
            }
        }

        // If no suitable block found
        if (!allocated) {
            printf("%d\t%d\t\tNot Allocated\n", files[i].file_no, files[i].file_size);
        }
    }
}

int main() {
    int n_blocks, n_files;

    // Input number of blocks and their sizes
    printf("Enter the number of blocks: ");
    scanf("%d", &n_blocks);
    struct Block blocks[n_blocks];

    for (int i = 0; i < n_blocks; i++) {
        blocks[i].block_no = i + 1;
        printf("Enter the size of block %d: ", i + 1);
        scanf("%d", &blocks[i].block_size);
        blocks[i].is_free = 1;
    }

    // Input number of files and their sizes
    printf("Enter the number of files: ");
    scanf("%d", &n_files);
    struct File files[n_files];

    for (int i = 0; i < n_files; i++) {
        files[i].file_no = i + 1;
        printf("Enter the size of file %d: ", i + 1);
        scanf("%d", &files[i].file_size);
    }

    // Run First Fit Allocation
    firstFit(blocks, n_blocks, files, n_files);

    return 0;
}

