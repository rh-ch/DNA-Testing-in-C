#include <stdio.h>
#include <string.h>

int calculate_score(char *sample, char *candidate) {
    int score = 0;
    int len = strlen(sample);
    int i;
    
    for (i = 0; i < len; ++i) {
        if (sample[i] == candidate[i]) {
            score += 3;
        } else if ((sample[i] == 'A' && candidate[i] == 'T') ||
                   (sample[i] == 'T' && candidate[i] == 'A') ||
                   (sample[i] == 'C' && candidate[i] == 'G') ||
                   (sample[i] == 'G' && candidate[i] == 'C')) {
            score += 1;
        }
    }
    
    return (score * 100) / (3 * len);
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }
    
    char sample[101];
    fscanf(fp, "%s", sample);

    int n;
    fscanf(fp, "%d", &n);
    
    char candidates[n][101]; 
    int scores[n]; 
    
    int i;
    for (i = 0; i < n; ++i) {
        fscanf(fp, "%s", candidates[i]);
        
        if (strcmp(sample, candidates[i]) == 0) {
            printf("Candidate %d is a perfect match.\n", i + 1);
            fclose(fp);
            return 0;
        }
        
        scores[i] = calculate_score(sample, candidates[i]);
    }
    
    fclose(fp);
    
    int best_index = 0;
    int highest_score = scores[0];
    
    for (i = 1; i < n; ++i) {
        if (scores[i] > highest_score) {
            highest_score = scores[i];
            best_index = i;
        }
    }

    printf("The best match is Candidate %d, with a score of %d.\n", best_index + 1, highest_score);
    
    return 0;
}
