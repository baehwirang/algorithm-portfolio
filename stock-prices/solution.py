def solution(prices):
    # 각 가격들의 기간을 담을 배열
    answer = [0] * len(prices)
    # 각 가격들의 인덱스를 저장할 스택
    # 기간 = (이후 처음으로 떨어진 가격의 인덱스 또는 최대) - (해당 가격의 인덱스)
    st = []

    # 각 가격을 인덱스와 함께 순회
    for i, price in enumerate(prices):
        # 스택엔 뭔가 있고, 가격이 떨어졌으면(가장 '최신'의 가격과 비교, 스택 특)
        while st and price < prices[st[-1]]:
            # 맨위에 있던 가격의 인덱스를 pop
            top_idx = st.pop()
            # 계산해서 결과에 넣어버려
            answer[top_idx] = i - top_idx
        # 현재 인덱스를 스택에 추가 (미래의 가격 하락을 기다림)
        st.append(i)

    # 아직까지 남아있다? 계속해서 가격이 떨어지지 않음 처리
    while st:
        top_idx = st.pop()
        answer[top_idx] = len(prices) - 1 - top_idx

    return answer