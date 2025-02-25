// 문제 설명
// A도둑과 B도둑이 팀을 이루어 모든 물건을 훔치려고 합니다. 단, 각 도둑이 물건을 훔칠 때 남기는 흔적이 누적되면 경찰에 붙잡히기 때문에, 두 도둑 중 누구도 경찰에 붙잡히지 않도록 흔적을 최소화해야 합니다.

// 물건을 훔칠 때 조건은 아래와 같습니다.

// 물건 i를 훔칠 때,
// A도둑이 훔치면 info[i][0]개의 A에 대한 흔적을 남깁니다.
// B도둑이 훔치면 info[i][1]개의 B에 대한 흔적을 남깁니다.
// 각 물건에 대해 A도둑과 B도둑이 남기는 흔적의 개수는 1 이상 3 이하입니다.
// 경찰에 붙잡히는 조건은 아래와 같습니다.

// A도둑은 자신이 남긴 흔적의 누적 개수가 n개 이상이면 경찰에 붙잡힙니다.
// B도둑은 자신이 남긴 흔적의 누적 개수가 m개 이상이면 경찰에 붙잡힙니다.
// 각 물건을 훔칠 때 생기는 흔적에 대한 정보를 담은 2차원 정수 배열 info, A도둑이 경찰에 붙잡히는 최소 흔적 개수를 나타내는 정수 n, B도둑이 경찰에 붙잡히는 최소 흔적 개수를 나타내는 정수 m이 매개변수로 주어집니다. 두 도둑 모두 경찰에 붙잡히지 않도록 모든 물건을 훔쳤을 때, A도둑이 남긴 흔적의 누적 개수의 최솟값을 return 하도록 solution 함수를 완성해 주세요. 만약 어떠한 방법으로도 두 도둑 모두 경찰에 붙잡히지 않게 할 수 없다면 -1을 return해 주세요.

// 제한사항
// 1 ≤ info의 길이 ≤ 40
// info[i]는 물건 i를 훔칠 때 생기는 흔적의 개수를 나타내며, [A에 대한 흔적 개수, B에 대한 흔적 개수]의 형태입니다.
// 1 ≤ 흔적 개수 ≤ 3
// 1 ≤ n ≤ 120
// 1 ≤ m ≤ 120

// 테스트 케이스 구성 안내
// 아래는 테스트 케이스 구성을 나타냅니다. 각 그룹 내의 테스트 케이스를 모두 통과하면 해당 그룹에 할당된 점수를 획득할 수 있습니다.

// 그룹	총점	테스트 케이스 그룹 설명
// #1	15%	info[i][1] = 1
// #2	40%	info의 길이 ≤ 20
// #3	45%	추가 제한 사항 없음

// 입출력 예
// info	n	m	result
// [[1, 2], [2, 3], [2, 1]]	4	4	2
// [[1, 2], [2, 3], [2, 1]]	1	7	0
// [[3, 3], [3, 3]]	7	1	6
// [[3, 3], [3, 3]]	6	1	-1

// 입출력 예 설명

// 입출력 예 #1

// 첫 번째와 세 번째 물건을 B도둑이 훔치고 두 번째 물건을 A도둑이 훔치면, A도둑에 대한 흔적은 총 2개이고 B도둑에 대한 흔적은 총 3개입니다. 목표를 달성하면서 A도둑에 대한 흔적 개수를 2보다 더 낮게 만들 수 없습니다.
// 따라서 2를 return 해야 합니다.

// 입출력 예 #2

// B도둑이 모든 물건을 훔쳐도 B의 흔적이 7개 이상 쌓이지 않습니다.
// 따라서 A도둑의 흔적은 최소 0이 되며, 0을 return 해야 합니다.

// 입출력 예 #3

// B도둑이 한 번이라도 물건을 훔치면 B의 흔적이 최소 1개 이상 남습니다. 따라서 모든 물건을 A도둑이 훔쳐야 하며, 이 경우에도 A의 흔적은 7개 미만입니다.
// 따라서, A도둑이 모든 물건을 훔칠 때의 흔적 개수 6을 return 해야 합니다.

// 입출력 예 #4

// 어떤 방법으로도 두 도둑 모두 경찰에 붙잡히지 않고 모든 물건을 훔칠 수 없습니다.
// 따라서 -1을 return 해야 합니다.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int a_factor = (*(int**)a)[0] - (*(int**)a)[1];
    int b_factor = (*(int**)b)[0] - (*(int**)b)[1];

    if (a_factor == b_factor) {
        return (*(int**)b)[0] - (*(int**)a)[0];
    } else {
        return b_factor - a_factor;
    }
}

// info_rows는 2차원 배열 info의 행 길이, info_cols는 2차원 배열 info의 열 길이입니다.
int solution(int** info, size_t info_rows, size_t info_cols, int n, int m) {
    int answer = 0;

    qsort(info, info_rows, sizeof(int*), compare);

    for (size_t i = 0; i < info_rows; i++) {
        if (m - info[i][1] > 0) {
            m -= info[i][1];
        } else {
            n -= info[i][0];
            answer += info[i][0];
        }
    }

    if (n <= 0) {
        return -1;
    } else {
        return answer;
    }
}

int main() {
    // given. result: 2.
    int values[3][2] = {{1, 2}, {2, 3}, {2, 1}};
    size_t info_rows = 3;
    size_t info_cols = 2;
    int n = 4;
    int m = 4;

    // given. result: 0.
    // int values[3][2] = {{1, 2}, {2, 3}, {2, 1}};
    // size_t info_rows = 3;
    // size_t info_cols = 2;
    // int n = 1;
    // int m = 7;

    // given. result: 6.
    // int values[3][2] = {{3, 3}, {3, 3}};
    // size_t info_rows = 3;
    // size_t info_cols = 2;
    // int n = 7;
    // int m = 1;

    // given. result: -1.
    // int values[3][2] = {{3, 3}, {3, 3}};
    // size_t info_rows = 3;
    // size_t info_cols = 2;
    // int n = 6;
    // int m = 1;

    // set param.
    int** info = malloc(info_rows * sizeof(int*));
    for (size_t i = 0; i < info_rows; i++) {
        info[i] = malloc(info_cols * sizeof(int));
        for (size_t j = 0; j < info_cols; j++) {
            info[i][j] = values[i][j];
        }
    }

    int answer = solution(info, info_rows, info_cols, n, m);
    printf("answer: %d\n", answer);

    for (size_t i = 0; i < info_rows; i++) {
        free(info[i]);
    }
    free(info);

    return 0;
}