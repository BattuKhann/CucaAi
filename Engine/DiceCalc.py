def three_vs_two():
    s1 = 0
    s2 = 0
    s3 = 0

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

    return tuple([s1, s2, s3])

def three_vs_one():
    s1 = 0
    s2 = 0
    s3 = 0

    for aa in range(1,7):
        for ab in range(1,7):
            for ac in range(1,7):
                for da in range(1,7):
                    attacking = [aa, ab, ac]
                    defending = [da]

                    attacking.sort(reverse=True)
                    aLoss = 0
                    dLoss = 0
                    
                    if attacking[0] > defending[0]:
                        dLoss += 1
                    else:
                        aLoss += 1

                    if aLoss == 1:
                        s1 += 1
                    elif dLoss == 1:
                        s3 += 1
                    else:
                        s2 += 1

    return tuple([s1, s2, s3])

def two_vs_two():
    s1 = 0
    s2 = 0
    s3 = 0

    for aa in range(1,7):
        for ab in range(1,7):
            for da in range(1,7):
                for db in range(1,7):
                    attacking = [aa, ab]
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

    return tuple([s1, s2, s3])

def two_vs_one():
    s1 = 0
    s2 = 0
    s3 = 0

    for aa in range(1,7):
        for ab in range(1,7):
            for da in range(1,7):
                attacking = [aa, ab]
                defending = [da]

                attacking.sort(reverse=True)
                aLoss = 0
                dLoss = 0
                
                if attacking[0] > defending[0]:
                    dLoss += 1
                else:
                    aLoss += 1

                if aLoss == 1:
                    s1 += 1
                elif dLoss == 1:
                    s3 += 1
                else:
                    s2 += 1
    return tuple([s1, s2, s3])
    
def one_vs_two():
    s1 = 0
    s2 = 0
    s3 = 0

    for aa in range(1,7):
        for da in range(1,7):
            for db in range(1,7):
                attacking = [aa]
                defending = [da, db]

                defending.sort(reverse=True)

                aLoss = 0
                dLoss = 0
                
                if attacking[0] > defending[0]:
                    dLoss += 1
                else:
                    aLoss += 1

                if aLoss == 1:
                    s1 += 1
                elif dLoss == 1:
                    s3 += 1
                else:
                    s2 += 1
    return tuple([s1, s2, s3])

def one_vs_one():
    s1 = 0
    s2 = 0
    s3 = 0

    for aa in range(1,7):
        for da in range(1,7):
            attacking = [aa]
            defending = [da]

            aLoss = 0
            dLoss = 0
            
            if attacking[0] > defending[0]:
                dLoss += 1
            else:
                aLoss += 1

            if aLoss == 1:
                s1 += 1
            elif dLoss == 1:
                s3 += 1
            else:
                s2 += 1
    return tuple([s1, s2, s3])

ret = three_vs_two()
print("3a vs 2d")
print(f's1: {ret[0]}')
print(f's2: {ret[1]}')
print(f's3: {ret[2]}')
print(f'Attacker Lost 2 Probability: {ret[0]/(ret[0]+ret[1]+ret[2])}')
print(f'Defender Lost 2 Probability: {ret[2]/(ret[0]+ret[1]+ret[2])}')
print(f'Both Lost 1 Probability: {ret[1]/(ret[0]+ret[1]+ret[2])}')

ret = three_vs_one()
print("3a vs 1d")
print(f's1: {ret[0]}')
print(f's2: {ret[1]}')
print(f's3: {ret[2]}')
print(f'Attacker Lost 1 Probability: {ret[0]/(ret[0]+ret[1]+ret[2])}')
print(f'Defender Lost 1 Probability: {ret[2]/(ret[0]+ret[1]+ret[2])}')
print(f'Both Lost 1 Probability: {ret[1]/(ret[0]+ret[1]+ret[2])}')

ret = two_vs_two()
print("2a vs 2d")
print(f's1: {ret[0]}')
print(f's2: {ret[1]}')
print(f's3: {ret[2]}')
print(f'Attacker Lost 2 Probability: {ret[0]/(ret[0]+ret[1]+ret[2])}')
print(f'Defender Lost 2 Probability: {ret[2]/(ret[0]+ret[1]+ret[2])}')
print(f'Both Lost 1 Probability: {ret[1]/(ret[0]+ret[1]+ret[2])}')

ret = two_vs_one()
print("2a vs 1d")
print(f's1: {ret[0]}')
print(f's2: {ret[1]}')
print(f's3: {ret[2]}')
print(f'Attacker Lost 1 Probability: {ret[0]/(ret[0]+ret[1]+ret[2])}')
print(f'Defender Lost 1 Probability: {ret[2]/(ret[0]+ret[1]+ret[2])}')
print(f'Both Lost 1 Probability: {ret[1]/(ret[0]+ret[1]+ret[2])}')

ret = one_vs_two()
print("1a vs 2d")
print(f's1: {ret[0]}')
print(f's2: {ret[1]}')
print(f's3: {ret[2]}')
print(f'Attacker Lost 1 Probability: {ret[0]/(ret[0]+ret[1]+ret[2])}')
print(f'Defender Lost 1 Probability: {ret[2]/(ret[0]+ret[1]+ret[2])}')
print(f'Both Lost 1 Probability: {ret[1]/(ret[0]+ret[1]+ret[2])}')

ret = one_vs_one()
print("1a vs 1d")
print(f's1: {ret[0]}')
print(f's2: {ret[1]}')
print(f's3: {ret[2]}')
print(f'Attacker Lost 1 Probability: {ret[0]/(ret[0]+ret[1]+ret[2])}')
print(f'Defender Lost 1 Probability: {ret[2]/(ret[0]+ret[1]+ret[2])}')
print(f'Both Lost 1 Probability: {ret[1]/(ret[0]+ret[1]+ret[2])}')