#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std ;

// 각 직선구간의 길이를 저장할 벡터
// 각 직선 구선 구간의 양 끝 좌표를 저장할 벡터(근데 이건 단순히 하나 좌표만 저장해도 충분)
// 0에서 각 직선 구간의 길이를 더해가면, 처음으로 sum의 결과 값보다 시간이 작아지는 시점의 좌표를 찾아서, 정확한 좌표 계산
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

/*
int main() {
    // 입출력 속도 향상
    
    // 1. 꼭짓점의 개수(K) 입력
    int K;
    std::cin >> K;

    // 2. 꼭짓점 좌표를 pair 벡터에 저장
    std::vector<std::pair<int, int>> vertices(K); // ?여기서 k를 따로 명시하면 차이가 있나?
    for (int i = 0; i < K; ++i) {
        std::cin >> vertices[i].first >> vertices[i].second;
    }

    // 3. 연속된 좌표들 사이의 거리를 계산하여 벡터에 저장
    std::vector<int> segment_lengths;
    long long total_length = 0; // 다각형의 총 둘레 (좌표 범위가 크므로 long long 사용)

    for (int i = 0; i < K; ++i) {
        // 현재 꼭짓점과 다음 꼭짓점(마지막 꼭짓점에서는 첫 번째 꼭짓점으로 순환)
        std::pair<int, int> current_v = vertices[i];
        std::pair<int, int> next_v = vertices[(i + 1) % K]; // % K 연산으로 마지막->처음 순환 처리 // ?이게 무슨 말? // 마지막 변을 위한 순환 처리

        // 수직/수평 거리는 x좌표 차이와 y좌표 차이의 절댓값의 합과 같음
        int length = std::abs(next_v.first - current_v.first) + std::abs(next_v.second - current_v.second);
        segment_lengths.push_back(length);
        total_length += length;
    }

    // 4. 확인할 시점(time point) 5개를 입력받음
    // 문제에서는 5개로 고정되어 있지만, 유연하게 처리하기 위해 vector 사용 가능
    for (int i = 0; i < 5; ++i) {
        int t;
        std::cin >> t;

        // 5-1. 시점이 다각형의 총 길이보다 크면 나머지 연산으로 조정
        // 로봇은 계속 순환하므로, 총 둘레로 나눈 나머지만큼 이동한 것과 같음
        if (total_length > 0) {
            t %= total_length;
        }

        // 5-2. 특정 시점의 좌표 계산
        int time_elapsed = 0;
        int final_x = 0, final_y = 0;

        for (int j = 0; j < K; ++j) {
            int current_segment_length = segment_lengths[j];

            // 현재 탐색하는 경로 구간 내에 목표 시점이 포함되는 경우
            if (t <= time_elapsed + current_segment_length) {
                // 현재 구간의 시작점과 끝점 좌표
                std::pair<int, int> start_v = vertices[j];
                std::pair<int, int> end_v = vertices[(j + 1) % K];

                // 이 구간에서 얼마나 더 이동해야 하는지 계산
                int time_on_segment = t - time_elapsed;

                // 이동 방향을 파악하여 최종 좌표 계산
                if (start_v.first == end_v.first) { // 수직 이동
                    final_x = start_v.first;
                    if (end_v.second > start_v.second) { // 위로 이동
                        final_y = start_v.second + time_on_segment;
                    } else { // 아래로 이동
                        final_y = start_v.second - time_on_segment;
                    }
                } else { // 수평 이동
                    final_y = start_v.second;
                    if (end_v.first > start_v.first) { // 오른쪽으로 이동
                        final_x = start_v.first + time_on_segment;
                    } else { // 왼쪽으로 이동
                        final_x = start_v.first - time_on_segment;
                    }
                }
                break; // 좌표를 찾았으므로 더 이상 탐색할 필요 없음
            }
            // 다음 구간으로 넘어가기 위해 현재 구간의 길이를 더해줌
            time_elapsed += current_segment_length;
        }

        // 결과 출력
        std::cout << final_x << " " << final_y << "\n";
    }

    return 0;
    
}
*/
