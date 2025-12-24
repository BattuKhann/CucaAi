s1 = 0 #attacker loses 2
s2 = 0 #both lose 1
s3 = 0 #defender loses 2

for aa in range(1,7):
    for ab in range(1,7):
        for ac in range(1,7):
            for da in range(1,7):
                for db in range(1,7):
                    attacking = [aa, ab, ac]
                    defending = [da, db]

                    attacking.sort(reverse=True)
                    defending.sort(reverse=True)

                    aLoss = 0
                    dLoss = 0
                    
                    if attacking[0] > defending[0]:
                        dLoss += 1
                    else:
                        aLoss += 1

                    if attacking[1] > defending[1]:
                        dLoss += 1
                    else:
                        aLoss += 1

                    if aLoss == 2:
                        s1 += 1
                    elif dLoss == 2:
                        s3 += 1
                    else:
                        s2 += 1
print(f's1: {s1}')
print(f's2: {s2}')
print(f's3: {s3}')
print(f'Attacker Lost 2 Probability: {s1/(s1+s2+s3)}')
print(f'Defender Lost 2 Probability: {s3/(s1+s2+s3)}')
print(f'Both Lost 1 Probability: {s2/(s1+s2+s3)}')
