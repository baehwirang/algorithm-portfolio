# 📈 자료구조 강의 'robocop' 문제 풀이

## 🎯 문제 해결 전략

각 직선구간의 길이를 저장할 벡터
각 직선 구선 구간의 양 끝 좌표를 저장할 벡터(근데 이건 단순히 하나 좌표만 저장해도 충분)
0에서 각 직선 구간의 길이를 더해가면, 처음으로 sum의 결과 값보다 시간이 작아지는 시점의 좌표를 찾아서, 정확한 좌표 계산

## 💻 핵심 코드

```c++
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std ;


int get_len(pair<int,int> p1, pair<int,int> p2){
    if(p1.first == p2.first) return abs(p1.second - p2.second) ;
    else return abs(p1.first - p2.first) ;
}

int main(){
    // 각 직선 구간의 길이를 저장할 벡터 생성
    vector<int> lengths ;
    // 각 좌표를 저장할 벡터 생성(각 좌표는, 위 직선 구간의 시작점에 해당), 위 두 컨테는 idx로 연결
    vector<pair<int,int>> xys ;
    // 좌표 갯수를 입력
    int xy_cnt ;
    cin >> xy_cnt ;
    // 좌표를 입력
    // 위 두가지 컨테이너 완성
    int x1 = -1 ;
    int y1 ;
    int x2, y2 ;
    for(int i=0 ; i<xy_cnt ; i++){
        cin >> x2 >> y2 ;
        xys.push_back({x2,y2}) ;
    }
    xys.push_back(xys[0]) ; // 아래 인덱스 이탈 방지용

    for(int i=0  ; i<xy_cnt-1 ; i++){
        int length = get_len(xys[i], xys[i+1]) ;
        lengths.push_back(length) ;
    }
    lengths.push_back(get_len(xys[0], xys[xy_cnt-1])) ; // 마지막과 처음 간의 거리도 추가 
    int total_len = accumulate(lengths.begin(), lengths.end(), 0) ; // 총 길이 계산
    // 시간대를 입력
    // 입력 받을 때마다 계산 및 출력
    // 계산
    for(int i=0 ; i<5 ; i++){
        int time ;
        cin >> time ;
        time %= total_len ; 
        // cout << i+1 << "번째 시간 " << time <<" 에 대한 출력 : " << endl ;
        pair<int, int> result ;
        

        int sum_lens = 0 ;
        for(int i=0 ; true ; i++){
            sum_lens += lengths[i] ;
            // cout << "\nsum" << sum_lens << "len" << lengths[i] << endl ;
            if(sum_lens > time){ // 등호는? time == total_len 가능? 불가
                // time이 길이 합에서 초과한 만큼을 저장
                int gap = time - (sum_lens-lengths[i]) ; 
                // cout << "sum_len = " << sum_lens << " gap : " << gap << endl ;
                auto p1 = xys[i] ; //  인덱스 이탈 문제는 xys의 마지막에 처음을 다시 추가
                auto p2 = xys[i+1] ; 
                // 처음으로 커지면
                // 해당 구간의 idx, idx+1에 저장된 좌표를 가져옴
                // 두 좌표가 수직인지 수평인지에 따라, 작은 좌표값을 가진 쪽에 (입력 시간)-(커지기 직전 함)을 더함
                if(p1.first == p2.first){
                    result.first = p1.first ;
                    if(p1.second > p2.second) 
                        result.second = p1.second - gap ;
                    else 
                        result.second = p1.second + gap ;
                }
                else{
                    // 세로 상황
                    result.second = p1.second ;
                    if(p1.first > p2.first) 
                        result.first = p1.first - gap ;
                    else 
                        result.first = p1.first + gap ;
                }
                break;
            }
        }
        // 결과를 출력
        cout << result.first << " " << result.second << "\n" ;
    }
    // 1. 입력 받은 시간을 전체 길이로 나눈 나머지 저장
    // 2. 0에서 각 구간의 길이를 저장할 벡터를 반복문을 통해 더함, 더할 때마다, 1.에서 저장한 값과 비교
    // 만약 작으면 다음 구간을 더함
    

    return 0 ;
}
```

## 🤔 배운 점 (Takeaway)

복잡해 보이는 문제도 작은 단위로 분해한 뒤, 하나씩 test 해보며 풀면 충분히 쉽게 풀 수 있다.