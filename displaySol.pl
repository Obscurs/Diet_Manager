extraBlank(N):- 
    N < 10, !, write(' ').
extraBlank(_).



extraBlankNum(N):-
    extraBlankAux(N).
extraBlankNum(_).



extraBlankAux(N):-
    N > 0,
    write(' '),
    N2 is N - 1,
    extraBlankAux(N2).

drawTail(D):-
    numDays(ND),
    D = ND, 
    write(' '), nl.
drawTail(_).


drawCell(D, Z, M2,Index):-
    % member(mdz-M-D-Z, M2),
    findall(mdz-Maux-D-Z, member(mdz-Maux-D-Z, M2), MealsDays),
    length(MealsDays,Len),
    Len > 0,
    TrueIndex is Index-1,
    nth0(TrueIndex,MealsDays,mdz-M-D-Z),
    meal(M,NAME,_,_,_,_), !,
    string_length(NAME,SIZE_NAME),
    BLANKS is 20 - SIZE_NAME,
    write(' '), write(NAME),
    extraBlankNum(BLANKS),

    % extraBlank(L), write(L), 
    % write('  ['), member(cr-C-R, M2), write('R:'), extraBlank(R), write(' '), write(R), write(']'),
    % write('  ['), member(ct-C-T, M2), write('T:'), extraBlank(T), write(' '), write(T), write(']'),
    write(' ').
drawCell(_,_, _,_):- 
    write('                      ').    

drawRow(Row, _):-
    limitMealsZone(LMZ),
    1 is Row mod (2+(LMZ-1)),
    H is Row // 2, 
    extraBlank(H), 
    write(' '), write(H), write('    '), 
    between(1, 162, _), write('='), 
    fail.
drawRow(Row, _):-
    limitMealsZone(LMZ),
    1 is Row mod (2+(LMZ-1)), !, nl.

drawRow(Row, M):-
    write('       |'),
    day(D),
    numDayZones(DZ),
    limitMealsZone(LMZ),
    Zone is (Row-1) // (LMZ+1)+1,
    % Zone is (Row-DZ*(LMZ-1)) // 2,
    Zone2 is (Row-1) mod (LMZ+1),
    drawCell(D,Zone, M, Zone2), 
    write('|'), 
    drawTail(D), 
    fail.
drawRow(_, _).



drawHeader:-
    nl, nl, 
    nl, nl, 
    write('               Monday                 Tuesday               Wednesday              Thursday                 Friday               Saturday                Sunday').

drawStats(M):-
    day(D),
    findall(md-Me-D, member(md-Me-D, M), MealsDays),
    getStatsListMealsAux(Pr,Cr,Fr,Kr,MealsDays),
    numProtesDay(Pgoal), numFatDay(Fgoal), numCarbDay(Cgoal),numKcalDay(Kgoal),
    DesvK is abs(Kr-Kgoal)/Kgoal*100,
    DesvP is abs(Pr-Pgoal)/Pgoal*100,
    DesvC is abs(Cr-Cgoal)/Cgoal*100,
    DesvF is abs(Fr-Fgoal)/Fgoal*100,
    write('Day '), write(D), write(':'),nl,
    write('Kcal: '), write(Kr), write('/'),write(Kgoal),write('('), write(DesvK), write('%)'), nl,
    write('Protes: '), write(Pr),write('/'),write(Pgoal),write('('), write(DesvP), write('%)'), nl,
    write('Carbs: '), write(Cr),write('/'),write(Cgoal),write('('), write(DesvC), write('%)'), nl,
    write('Fat: '), write(Fr),write('/'),write(Fgoal),write('('), write(DesvF), write('%)'), nl,nl,
    fail.
drawStats(_).


writeIngredients(Res):-
    member(ing-I-N-A-S-U,Res),
    A < 0,
    BuyAmount is ceil(abs(A*S)),
    write(I), write(' '),write(N),write(' '),write(BuyAmount),write(' '),write(U),nl,
    fail.
writeIngredients(_).
substractMealToIngredients(Res,[],[],Res).
substractMealToIngredients(I,[ID|ListIng],[Amount|ListAmounts],Res2):-
    concat(PrevIng,[ing-ID-Name-AmountPrev-Stack-Unit|PostIng],I),
    AmountNew is AmountPrev-Amount,
    concat(PrevIng,[ing-ID-Name-AmountNew-Stack-Unit|PostIng],Res),
    substractMealToIngredients(Res,ListIng,ListAmounts,Res2).

substractMealsToIngredients(Res,[],Res).
substractMealsToIngredients(I,[M|MS],Res2):-
    meal(M,_,ListIng,ListAmounts,_,_),
    substractMealToIngredients(I,ListIng,ListAmounts,Res),
    substractMealsToIngredients(Res,MS,Res2).

drawIngredients(M):-
    findall(ing-I-N-A-Stack-Unit,(ingredient(I),component(I,N,_,_,_,_,_,A,_,Stack,Unit)),Ingredients),
    findall(Meal,member(md-Meal-_,M),Meals),
    substractMealsToIngredients(Ingredients,Meals,Res),
    writeIngredients(Res).


displaySchedule(M):-
    drawStats(M),
    drawIngredients(M),
    drawHeader, nl,
    numDayZones(DZ),
    limitMealsZone(LMZ),
    NumRows is DZ*2+ DZ*(LMZ-1),
    between(1, NumRows, Row), 
    drawRow(Row, M), 
    fail.

