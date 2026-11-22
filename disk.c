
#include <stdio.h>
#include <stdlib.h>

#define N 8

int req[N] = {98, 183, 37, 122, 14, 124, 65, 67};
int head = 53;
int disk_size = 200;
int direction = 1;  // 1 = Right, 0 = Left


// FCFS
void fcfs(int req[], int n_req, int head) {

    int total = 0;

    printf("\nFCFS: %d -> ", head);

    for (int i = 0; i < n_req; i++) {
        total += abs(head - req[i]);
        head = req[i];
        printf("%d -> ", head);
    }

    printf("\nTotal Head Movement: %d\n", total);
}


// SSTF
void sstf(int req[], int n_req, int head) {

    int total = 0;
    int visited[n_req];

    for (int i = 0; i < n_req; i++) {
        visited[i] = 0;
    }

    printf("\nSSTF: %d -> ", head);

    for (int i = 0; i < n_req; i++) {

        int min = 999999;
        int index = -1;

        for (int j = 0; j < n_req; j++) {

            if (visited[j] == 0) {

                int distance = abs(head - req[j]);

                if (distance < min) {
                    min = distance;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        total += min;
        head = req[index];

        printf("%d -> ", head);
    }

    printf("\nTotal Head Movement: %d\n", total);
}


// SCAN
void scan(int req[], int n_req, int head, int disk_size, int direction) {

    int arr[n_req + 1];
    int total = 0;
    int pos = 0;

    for (int i = 0; i < n_req; i++) {
        arr[i] = req[i];
    }

    arr[n_req] = head;

    // Sorting
    for (int i = 0; i <= n_req; i++) {
        for (int j = i + 1; j <= n_req; j++) {

            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Find head position
    while (pos <= n_req && arr[pos] != head) {
        pos++;
    }

    printf("\nSCAN: %d -> ", head);

    if (direction == 1) {

        // Move right
        for (int i = pos + 1; i <= n_req; i++) {
            total += abs(head - arr[i]);
            head = arr[i];
            printf("%d -> ", head);
        }

        // Reach disk end
        if (head != disk_size - 1) {
            total += abs(head - (disk_size - 1));
            head = disk_size - 1;
            printf("%d -> ", head);
        }

        // Move left
        for (int i = pos - 1; i >= 0; i--) {
            total += abs(head - arr[i]);
            head = arr[i];
            printf("%d -> ", head);
        }
    }

    else {

        // Move left
        for (int i = pos - 1; i >= 0; i--) {
            total += abs(head - arr[i]);
            head = arr[i];
            printf("%d -> ", head);
        }

        // Reach disk beginning
        if (head != 0) {
            total += head;
            head = 0;
            printf("%d -> ", head);
        }

        // Move right
        for (int i = pos + 1; i <= n_req; i++) {
            total += abs(head - arr[i]);
            head = arr[i];
            printf("%d -> ", head);
        }
    }

    printf("\nTotal Head Movement: %d\n", total);
}


// C-SCAN
void cscan(int req[], int n_req, int head, int disk_size, int direction) {

    int arr[n_req + 1];
    int total = 0;
    int pos = 0;

    for (int i = 0; i < n_req; i++) {
        arr[i] = req[i];
    }

    arr[n_req] = head;

    // Sorting
    for (int i = 0; i <= n_req; i++) {
        for (int j = i + 1; j <= n_req; j++) {

            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Find head position
    while (pos <= n_req && arr[pos] != head) {
        pos++;
    }

    printf("\nC-SCAN: %d -> ", head);

    if (direction == 1) {

        // Move right
        for (int i = pos + 1; i <= n_req; i++) {
            total += abs(head - arr[i]);
            head = arr[i];
            printf("%d -> ", head);
        }

        // Reach disk end
        total += (disk_size - 1 - head);
        head = disk_size - 1;
        printf("%d -> ", head);

        // Jump to beginning
        total += disk_size - 1;
        head = 0;
        printf("%d -> ", head);

        // Continue right
        for (int i = 0; i < pos; i++) {
            total += abs(head - arr[i]);
            head = arr[i];
            printf("%d -> ", head);
        }
    }

    else {

        // Move left
        for (int i = pos - 1; i >= 0; i--) {
            total += abs(head - arr[i]);
            head = arr[i];
            printf("%d -> ", head);
        }

        // Reach disk beginning
        total += head;
        head = 0;
        printf("%d -> ", head);

        // Jump to disk end
        total += disk_size - 1;
        head = disk_size - 1;
        printf("%d -> ", head);

        // Continue left
        for (int i = n_req; i > pos; i--) {
            total += abs(head - arr[i]);
            head = arr[i];
            printf("%d -> ", head);
        }
    }

    printf("\nTotal Head Movement: %d\n", total);
}


// Main function
int main() {

    printf("Disk Scheduling Algorithms\n");

    printf("\nRequest Queue: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", req[i]);
    }

    printf("\nInitial Head: %d", head);
    printf("\nDisk Size: %d", disk_size);
    printf("\nDirection: %s\n", direction == 1 ? "Right" : "Left");

    fcfs(req, N, head);
    sstf(req, N, head);
    scan(req, N, head, disk_size, direction);
    cscan(req, N, head, disk_size, direction);

    return 0;
}
