#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    printf("Enter number of processes and resources:\n");
    scanf("%d %d", &n, &m);

    int alloc[n][m], request[n][m], avail[m];
    bool finish[n];

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter request matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Initialize finish array
    for (int i = 0; i < n; i++) {
        
        for (int j = 0; j < m; j++) {
            if (alloc[i][j] == 0) {
                finish[i] = true;
            
            }else{
                finish[i]=false;
            }
     
    }
bool changed = true;
while(changed){
    changed = false;
    for(int i=0; i< n; i++){
        if(!finish[i]){
            bool canAlloc = true;
            for(int j=0; j<m; j++){
                if(request[i][j] >= avail[j]){
                    canAlloc = false;
                    break;
                }
            }
            if(canAlloc){
                for(int j=0; j<m; j++){
                    avail[j] += alloc[i][j];
                }
                changed = true;
                finish[i] = true;

            }
    }
    
}
}
}
