# 개관
알고리즘
* 컴퓨터가 따라할 수 있도록 자세히 설명한 과정을 나타냄
* 모호해서는 안된다.

시간
* 얼마나 빨리 수행되는지

공간
* 적은 용량의 메모리를 사용한다는 이야기

# 4. 알고리즘의 시간 복잡도 분석
## 4.1 도입
알고리즘은 언제나 같은 속도로 동작하지 않음
* 입력의 크기나 특성에 따라 달라질 수 있다.
* 어떤 기준으로 수행시간을 측정?

### 반복문이 지배한다.
지배한다(dominate)
* 한 가지 항목이 전체의 대소를 좌지우지 하는 것

알고리즘의 수행 시간을 지배하는 것 - 반복문
* 입력의 크기가 커질수록 반복문이 알고리즘의 수행 시간을 지배하게 됨

## 4.2 선형 시간 알고리즘
### 다이어트 현황 파악: 이동 평균 계산하기
이동 평균(moving average)
* 시간에 따라 변화하는 값들을 관찰할 때 유용하게 사용할 수 있는 통계적 기준

M-이동 평균
* 마지막 M개의 관찰 값의 평균으로 정의
* 새 관찰 값이 나오면 M-이동 평균은 새 관찰 값을 포함하도록 바뀜

구하는 법
* 지난 M개 측정치의 합을 구하고 M으로 나누면 된다.

N^2 복잡도의 이동 평균 구하기
```C++
// 실수 배열 A가 주어질 때, 각 위치에서 M-이동 평균 값을 구한다.
vector<double> movingAverage1(const vector<double>& A, int M)
{
    vector<double> ret;
    int N = A.size();

    for (int i = M - 1; i < N; ++i)
    {
        // A[i]까지의 이동 평균 값을 구하자
        double partialSum = 0;
        for (int j = 0; j < M; ++j)
        {
            partialSum += A[i - j];
        }

        ret.push_back(partialSum / M);

    }

    return ret;
}
```
* 이 방식은 실수 배열 A의 크기가 커질 수록 계산횟수가 엄청나게 늘어난다.

어떻게 좀 더 빠른 방식으로 구할 수 있을까
* M-1일부터 이동 평균을 계산
* M-1일의 이동 평균과 M일의 이동 평균에 포함되는 숫자를 찾아보자.
* 0일과 M일의 몸무게를 제외하면 전부 겹친다.
* M-1일에 구했던 몸무게의 합에서 0일째에 측정한 몸무게를 빼고 M일째에 측정한 몸무게를 더하자.

N 복잡도의 이동 평균 구하기
```C++
vector<double> movingAverage1(const vector<double>& A, int M)
{
    vector<double> ret;
    int N = A.size();
    double partialSum = 0;

    for (int i = 0; i < M - 1; ++i)
    {
        partialSum += A[i];
    }

    for (int i = M - 1; i < N; ++i)
    {
        // M일째 더해주기
        partialSum += A[i];
        ret.push_back(partialSum / M);
        // 0일째 빼주기
        partialSum -= A[i - M + 1];
    }

    return ret;
}
```
* 정확히 선형 시간 알고리즘이 된다!

## 4.3 선형 이하 시간 알고리즘
### 이진 탐색
binary search 알고리즘 binsearch(A[], x)
* 오름차순으로 정렬된 배열 A[]와 찾고 싶은 값 x가 주어질 때 A[i-1] < x <= A[i]인 i를 반환
* 이때 A[-1] = -무한대, A[N] = 무한대로 가정

### 그래도 선형 시간 아닌가요?
알고리즘 수행 전 모두 시간 순으로 정렬해야 한다.
* 그러나 이렇게 분석하지 않는다.

이유
* A[]를 실제로 계산해서 갖고 있을 필요가 없다.
  * 필요한 부분만 계산해서 판단하면 된다.
  * i가 주어질 때 A[i]의 값을 직접 계산하는 콜백 함수를 제공하는 방법 등으로
* 정렬 과정은 찾는 작업과는 별개이다.

## 4.4 지수 시간 알고리즘
### 다항 시간 알고리즘
N과 N^2 그외의 N 거듭제곱의 선형 결합으로 이루어진 식
* 대다수의 알고리즘은 다항 시간

N^100 그 이상도 다항 시간
* 그런데 왜 이들을 묶어서 이름을 붙일까?
* 다항 시간보다 오랜 시간이 걸리는 알고리즘이 있기 때문

### 지수 시간 알고리즘
2^m 시간 알고리즘
* 전체 수행 시간에 엄청난 영향을 미친다.
* N이 하나 증가할 때마다 걸리는 시간이 배로 증가하는 알고리즘
* 지수 시간보다 빠른 알고리즘을 찾지 못한 문제들이 전산학에는 쌓여있다.
* 지수 시간(exponential time)

### 소인수 분해의 수행 시간

## 4.5 시간 복잡도

## 4.6 수행 시간 어림짐작하기
### 주먹구구 법칙
많은 경우에서 시간 복잡도와 입력 크기만 알고 있더라도 어떤 알고리즘이 시간 안에 동작할지 짐작하는 것이 가능
* 시간 복잡도는 수행 시간에 가장 큰 영향을 미치는 요소

주먹구구 법칙
* 입력의 크기를 시간 복잡도에 대입해서 얻은 반복문 수행 횟수에 대해, 1초당 반복문 수행 횟구가 1억(10^8)이 넘어가면 시간 제한을 초과할 가능성이 있다.

### 주먹구구 법칙은 주먹구구일 뿐이다
시간 복잡도 외에 고려해야할 요소들
* 시간 복잡도가 프로그램의 실제 수행 속도를 반영하지 못하는 경우
* 반복문의 내부가 복잡한 경우
* 메모리 사용 패턴이 복잡한 경우
* 언어와 컴파일러의 차이
* 구형 컴퓨터를 사용하는 경우

### 실제 적용해보기
구간 합을 구하는 문제

N^3 시간 복잡도의 무식한 알고리즘
```C++
const int MIN = numeric_limits<int>::min();

// A[]의 연속된 부분 구간의 최대 합을 구한다.
int inefficientMaxSum(const vector<int>& A)
{
    int N = A.size();
    int ret = MIN;

    for (int i = 0; i < N; ++i)
    {
        for (int j = i; j < K; ++j)
        {
            int sum = 0;

            for (int k = i; k <= j; ++k)
                sum += A[k];

            ret = max(ret, sum);
        }
    }

    return ret;
}
```

N^2의 시간 복잡도의 알고리즘
```C++
const int MIN = numeric_limits<int>::min();

// A[]의 연속된 부분 구간의 최대 합을 구한다.
int betterMaxSum(const vector<int>& A)
{
    int N = A.size();
    int ret = MIN;

    for (int i = 0; i < N; ++i)
    {
        int sum = 0;

        // 구간 A[i..j]의 합을 구한다.
        for (int j = i; j < N; ++j)
        {
            sum += A[j];
            ret = max(ret, sum);
        }
    }

    return ret;
}
```

NlgN의 분할 정복 알고리즘
```C++
// A[lo..hi]의 연속된 부분 구간의 최대 합을 구한다.
int fastMaxSum(const vector<int>& A, int lo, int hi)
{
    // 기저 사례: 구간의 길이가 1일 경우
    if (lo == hi) return A[lo];

    // 배열을 A[lo..mid], A[mid+1..hi]의 두 조각으로 나눈다.
    int mid = (lo + hi) / 2;

    // 두 부분에 모두 걸쳐 있는 최대 합 구간을 찾는다.
    // A[i..mid]와 A[mid+1..j] 형태를 갖는 구간의 합으로 이루어진다.
    // A[i..mid] 형태를 갖는 최대 구간을 찾는다.
    int left = MIN, right = MIN, sum = 0;
    for (int i = mid; i >= lo; --i)
    {
        sum += A[i];
        left = max(left, sum);
    }

    // A[mid+1..j] 형태를 갖는 최대 구간을 찾는다.
    sum = 0;
    for (int j = mid + 1; j <= hi; ++j)
    {
        sum += A[j];
        right = max(right, sum);
    }

    // 최대 구간이 두 조각 중 하나에만 속해 있는 경우의 답을 재귀 호출로 찾는다.
    int single = max(fastMaxSum(A, lo, mid), fastMaxSum(A, mid+1, hi));

    // 두 경우 중 최대치를 반환한다.
    return max(left + right, single);
}
```

선형 시간으로 해결할 수 있는 동적 계획법
* maxAt(i) = max(0, maxAt(i - 1)) + A[i]

```C++
int fastestMaxSum(const vector<int>& A)
{
    int N = A.size(), ret = MIN, psum = 0;
    
    for (int i = 0; i < N; ++i)
    {
        psum = max(psum, 0) + A[i];
        ret = max(psum, ret);
    }

    return ret;
}
```