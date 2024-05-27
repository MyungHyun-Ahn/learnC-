# 06. 무식하게 풀기
## 6.1 도입
무식하게 푼다(brute-force)
* 컴퓨터의 빠른 계산 능력을 이용해 가능한 경우의 수를 일일이 나열하며 답을 찾는 방법
* 이런 알고리즘을 완전 탐색(exhaustive search)이라고 부름

완전 탐색은 사실 컴퓨터의 장점을 가장 잘 이용하는 방법
* 컴퓨터의 최대 장점 : 속도가 빠르다.
* 손으로 풀기에 경우의 수가 너무 많은 경우
  * 컴퓨터로 충분히 빠르면서 가장 구현하기 쉬운 대안

## 6.2 재귀 호출과 완전 탐색
### 재귀 호출
보는 범위가 작아질수록 각 조각의 형태가 유사해지는 작업
* 완전히 같은 코드를 반복해 실행하는 for 같은 반복문
* 이런 작업을 구현할 때 유용하게 사용되는 개념
  * 재귀 함수(recursive function) 혹은 재귀 호출(recursion)

재귀 호출의 기초적인 성질을 이해하기 위해 가장 간단한 반복문을 재귀함수로 바꿔 구현해보자

1부터 n까지의 합을 계산하는 반복함수와 재귀 함수
```C++
// 필수 조건 n >= 1
// 결과: 1부터 n까지의 합을 반환한다.
int sum(int n)
{
    int ret = 0;
    for (int i = 1; i <= n; ++i)
        ret += i;
    return ret;
}

// 필수 조건 n >= 1
// 결과: 1부터 n까지의 합을 반환한다.
int recursiveSum(int n)
{
    if (n == 1) return 1; // 더이상 쪼개지지 않을 때
    return n + recursiveSum(n - 1);
}
```

재귀 호출의 기저 사례(base case)
* 더이상 쪼개지지 않는 가장 작은 작업
* 모든 재귀 함수는 '더이상 쪼개지지 않는' 최소한의 작업에 도달했을 때 답을 곧장 반환하는 조건문을 포함해야 함

재귀 호출의 장점
* 기존의 반복문을 사용해 작성하던 코드를 다르게 짤 수 있는 방법을 제공해줌
* 문제의 특성에 따라 재귀 호출은 코딩을 훨씬 간편하게 해 줄 수 있는 강력한 무기가 됨

### 예제: 중첩 반복문 대체하기
번호 매겨진 n개의 원소 중 네 개를 고르는 모든 경우를 출력하는 코드
```C++
for (int i = 0; i < n; ++i)
    for (int j = i + 1; i < n; ++j)
        for (int k = j + 1; k < n; ++k)
            for (int l = k + 1; l < n; ++l)
                cout << i << " " << j << " " << k << " " << k << " " << l << endl;
```

위 코드 조각이 하는 작업 네 개로 나눌 수 있음
* 각 조각에서 하나의 원소를 고르는 것
* 남은 원소들을 고르는 작업을 자기 자신을 호출해 떠넘기는 재귀 함수를 작성

남은 원소들을 고르는 '작업'을 다음과 같은 입력들의 집합으로 정의 가능
* 원소들의 총 개수
* 더 골라야 할 원소들의 개수
* 지금까지 고른 원소들의 번호

n개의 원소 중 m개를 고르는 모든 조합을 찾는 알고리즘
```C++
// n: 전체 원소의 수
// picked: 지금까지 고른 원소들의 번호
// toPock: 더 고를 원소의 수
// 일 때, 앞으로 toPick개의 원소를 고르는 모든 방법을 출력한다.
void pick(int n, vector<int>& picked, int toPick)
{
    // 기저 사례: 더 고를 원소가 없을 때 고른 원소들을 출력한다.
    if (toPick == 0)
    {
        printPicked(picked);
        return;
    }

    // 고를 수 있는 가장 작은 번호를 계산한다.
    int smallest = picked.empty() ? 0 : picked.back() + 1;

    // 이 단계에서 원소 하나를 고른다.
    for (int next = smallest; next < n; ++next)
    {
        picked.push_back(next);
        pick(n, picked, toPick - 1);
        picked.pop_back();
    }
}
```

## 예제: 보글 게임 (문제 IDL BOGGLE, 난이도: 하)

문제 링크
* https://www.algospot.com/judge/problem/read/BOGGLE

다음과 같은 함수를 작성하면 된다.
* hasWord(y, x, word) = 보글 게임판의 (y, x)에서 시작하는 단어 word의 존재 여부를 반환

이 문제를 풀 때 가장 까다로운 점
* 다음 글자가 될 수 있는 칸이 여러 개 있을 때 이 중 어느 글자를 선택해야 할지 미리 알 수 없다는 점
* 가장 간단한 방법 완전 탐색을 이용하여 단어를 찾아낼 때까지 모든 인접한 칸을 하나씩 시도해 보는 것

### 문제의 분할
hasWord()가 하는 일을 가장 자연스럽게 조각내는 방법
* 각 글자를 하나의 조각으로 만드는 것
* 단어의 시작 부분에서 8방향을 모두 탐색

### 기저 사례의 선택
더 이상의 탐색 없이 간단히 답을 낼 수 있는 다음의 경우를 기저 사례로 선택
1. 위치 (y, x)에 있는 글자가 원하는 단어의 첫 글자가 아닌 경우 항상 실패
2. (1번 경우에 해당하지 않는 경우) 원하는 단어가 한 글자인 경우 항상 성공
    * 두 조건 간 순서는 바꾸면 안됨

간결한 코드를 작성하는 유용한 팁
* 기저 사례를 맨 처음에 처리
* 함수를 호출하는 시점에서 이런 오류를 검사할 필요가 없음

### 구현
위 모든 것을 결합
```C++
const int dx[8] = { -1, -1, -1,  1,  1,  1,  0,  0 };
const int dy[8] = { -1,  0,  1, -1,  0,  1, -1,  1 };

// 5x5의 보글 게임 판의 해당 위치에서 주어진 단어가 시작하는지 반환
bool hasWord(int y, int x, const string& word)
{
    // 기저 사례 1: 시작 위치가 범위 밖이면 무조건 실패
    if (!inRange(y, x)) return false;

    // 기저 사례 2: 첫 글자가 일치하지 않으면 실패
    if (board[y][x] != word[0]) return false;

    // 기저 사례 3: 단어 길이가 1이면 성공
    if (word.size() == 1) return true;

    // 인접한 여덟 칸을 검사한다.
    for (int direction = 0; direction < 8; ++direction)
    {
        int nextY = y + dy[direction];
        int nextX = x + dy[direction];

        // 다음 칸이 범위 안에 있는지, 첫 글자는 일치하는지 확인할 필요가 없다.
        if (hasWord(nextY, nextX, word.substr(1)))
            return true;
    }

    return false;
}
```

### 시간 복잡도 분석
후보의 최대 수를 계산
* 8^n (n = 단어의 수)
* 단어의 길이가 짧을 경우에만 완전 탐색으로 해결 가능
* 다른 장에서 다루는 설계 패러다임을 사용해야 함

### 완전 탐색 레시피
1. 완전 탐색은 존재하는 모든 답을 하나씩 검사하므로, 걸리는 시간은 가능한 답의 수에 비례함
   * 최대 크기의 입력을 가정했을 때 답의 개수를 계산하고 이들을 모두 제한 시간 안에 생성할 수 있을지를 가늠해야 함
   * 만약 시간 안에 계산할 수 없다면 다른 알고리즘을 사용
2. 가능한 모든 답의 후보를 만드는 과정을 여러 개의 선택으로 나눔
   * 각 선택은 답의 후보를 만드는 과정의 한 조각이 됨
3. 그중 하나의 조각을 선택해 답의 일부를 만들고, 나머지 답을 재귀 호출을 통해 완성
4. 조각이 하나밖에 남지 않은 경우, 혹은 하나도 남지 않은 경우에는 답을 생성 했으므로, 이것을 기저 사례로 선택하여 처리

### 이론적 배경: 재귀 호출과 부분 문제
재귀 호출을 공부하면서 짚고 넘어가야 할 중요한 개념 중 하나
* 문제(problem)와 부분 문제(subproblem)

재귀 호출을 논의할 때 '문제'란
* 항상 수행해야 할 작업과 그 작업을 적용할 자료의 조합을 의미

원래 문제의 '부분 문제'
* 문제의 일부
* 문제의 한 조각

## 6.3 문제: 소풍 (문제 ID: PICNIC, 난이도: 하)

문제 링크
* https://www.algospot.com/judge/problem/read/PICNIC

## 6.4 풀이: 소풍
### 완전 탐색
가장 간단한 방법
* 완전 탐색을 이용해 조합을 모두 만들어 보는 것

재귀 호출을 이용해 문제를 해결
* 각 답을 만드는 과정을 여러 개의 조각으로 나누어야 함
* 전체 문제를 n/2로 나누어 한 조각마다 두 학생을 짝지어주는 것으로 함

이때 문제의 형태
* 아직 짝을 찾지 못한 학생들의 명단이 주어질 때 친구끼리 둘씩 짝짓는 경우의 수를 계산하라

### 중복으로 세는 문제
위 아이디어를 그대로 코드로 옮긴 것
```C++
int n;
bool areFriends[10][10];

// taken[i] = i번째 학생이 짝을 이미 찾았으면 true, 아니면 false
int countPairings(bool taken[10])
{
    // 기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    bool finished = true;
    for (int i = 0; i < n; ++i)
        if (!taken[i])
            finished = false;

    if (finished)
        return 1;

    int ret = 0;
    // 서로 친구인 두 학생을 찾아 짝을 지어 준다.
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (!taken[i] && !taken[j] && areFriends[i][j])
            {
                taken[i] = taken[j] = true;
                ret += countPairings(taken);
                taken[i] = taken[j] = false;
            }
    return ret;
}
```

코드에 두 가지 문제점이 있다.
* 같은 학생 쌍을 두 번 짝지어 준다.
* 다른 순서로 학생들을 짝지어 주는 것을 서로 다른 경우로 세고 있다.

해결법
1. 같은 답 중 사전순으로 먼저 오는 답 하나만을 센다.
2. 항상 번호가 가장 빠른 학생부터 짝을 짓기 때문에 위 두 가지 문제점 모두 해결된다.

문제를 해결한 재귀 호출 코드
```C++
int n;
bool areFriends[10][10];

// taken[i] = i번째 학생이 짝을 이미 찾았으면 true, 아니면 false
int countPairings(bool taken[10])
{
    // 남은 학생들 중 가장 번호가 빠른 학생을 찾는다.
    int firstFree = -1;

    for (int i = 0; i < n; ++i)
    {
        if (!taken[i])
        {
            firstFree = i;
            break;
        }
    }

    // 기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    if (firstFree == -1)
        return 1;

    int ret = 0;
    // 이 학생과 짝지을 학생을 결정한다.
    for (int pairWith = firstFree + 1; pairWith < n; ++pairWith)
        if (!taken[pairWith] && !taken[firstFree] && areFriends[firstFree][pairWith])
        {
            taken[firstFree] = taken[pairWith] = true;
            ret += countPairings(taken);
            taken[firstFree] = taken[pairWith] = false;
        }
    return ret;
}
```

### 답의 수 상한
재귀 호출 알고리즘은 답의 수에 정비례 하는 시간을 가짐
* 이 문제에서 가장 많은 답을 가질 수 있는 입력은 열 명의 학생이 모두 서로 친구인 경우