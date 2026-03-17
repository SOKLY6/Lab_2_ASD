people, without_base_card, with_reserve_card = map(int, input().split())
array_without_base_card = list(int, input().split())
array_with_reserve_card = list(int, input().split())
max_people = 0
for i in range(1, people+1):
    if i not in array_without_base_card:
        max_people += 1
        continue
    elif i in array_without_base_card and i in array_with_reserve_card:
        max_people += 1
        array_without_base_card.remove(i)
        continue
    else:
        if i > 1 and (i-1) in array_with_reserve_card:
            array_without_base_card.remove(i)
            array_with_reserve_card.remove(i-1)
            max_people += 1
            continue
        if i <= 10 and (i+1) in array_with_reserve_card:
            array_without_base_card.remove(i)
            array_with_reserve_card.remove(i+1)
            max_people += 1
            continue

print(max_people)