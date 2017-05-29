:-include(entradaHoraris).
:-include(displaySol).
:-dynamic(varNumber/3).


pert(X, [X|_]).
pert(X, [_|L]):- pert(X,L).

pert_con_resto(X,L,R) :- concat(L1,[X|L2],L), concat(L1,L2,R).

concat([], List, List).
concat([Head|Tail], List, [Head|Rest]) :-
    concat(Tail, List, Rest).

subset([],[],[]).
subset(S1Tail,[L|S2Tail],[L|LS]):-
	subset(S1Tail,S2Tail,LS).
subset([L|S1Tail],S2Tail,[L|LS]):-
	subset(S1Tail,S2Tail,LS).

isSubset([],_).
isSubset([S|Sub],Set):-
	pert(S,Set),
	isSubset(Sub,Set).

% [a,e,c] o [a,b,d]
% [[[a,e,c],a],[[a,e,c],b],[[a,e,c],d]]

subsetRemove([],_,[]).
subsetRemove([S|Elems],CNF,[S|Res]):-
	isPrimalSet(S,CNF),!,
	subsetRemove(Elems,CNF,Res).

subsetRemove([_|Elems],CNF,Res):-
	subsetRemove(Elems,CNF,Res).
	

isPrimalSet(_,[]).
isPrimalSet(S,[X|CNF]):-
	\+isSubset(X,S),
	isPrimalSet(S,CNF).
isPrimalSet(S,[X|CNF]):-
	isSubset(X,S),
	isSubset(S,X),
	isPrimalSet(S,CNF).



distributeOne(_,[],[]).
distributeOne(L1,[X|L2],Result):-
	findall([X,E],pert(E,L1),ResAux),
	concat(ResAux,ResNext,Result),
	distributeOne(L1,L2,ResNext).

distributeMult([],_,[]).
distributeMult([D1|Drest],D2,Result):-
	distributeOne(D1,D2,ResD1),
	concat(ResD1,ResNext,Result),
	distributeMult(Drest,D2,ResNext).

distributeMult2([],_,[]).
distributeMult2([D1|Drest],D2,Result):-
	distributeOne(D1,D2,ResD1),
	concat(ResD1,ResNext,Result),
	distributeMult2(Drest,D2,ResNext).


distributeCNFmult([],_,[]).
distributeCNFmult([C1|Crest],DL,Result):-
	distributeCNF(C1,DL,Res),
	concat(Res,ResNext,Result),
	distributeCNFmult(Crest,DL,ResNext),!.


distributeCNF(_,[],_).
distributeCNF(CNF,DNF,Res):-
	findall([D|CNF],pert(D,DNF),Res).

distributeCNF2(_,[],Res,Res).
distributeCNF2(CNF,[D2|Drest],Result,ResEnd):-
	findall([C,D2],pert(C,CNF),Res),
	concat(Res,Result,Result2),
	distributeCNF2(CNF,Drest,Result2,ResEnd).

funcDNFtoCNFaux([],CNF,CNF).
funcDNFtoCNFaux([D2|DNF],CNF,Res):-

	distributeCNFmult(CNF,D2,CNF2),
	removeRepeatedElemsCNF(CNF2,CNFaux1),
	sort(CNFaux1,CNFsimple),
	funcDNFtoCNFaux(DNF,CNFsimple,Res).

funcDNFtoCNF([X],[X]).
funcDNFtoCNF([X|DNF],Result):-
	pert_con_resto(Y,DNF,DNF2),!,
	distributeOne(X,Y,CNF),
	funcDNFtoCNFaux(DNF2,CNF,ResultAux1),
	removeRepeatedElemsCNF(ResultAux1,ResultAux2),
	sort(ResultAux2,Result).
	% subsetRemove(ResultAux3,ResultAux3,Result).

writeCNF([]).
writeCNF([C|CNF]):-
	writeClause(C),
	writeCNF(CNF).


removeRepeatedElemsCNF([],[]).
removeRepeatedElemsCNF([E|CNF],[X|Result]):-
	sort(E,X),
	removeRepeatedElemsCNF(CNF,Result).

createCombClauses(_,[]).
createCombClauses(COMB,[MD|MDLS]):-
	negate(COMB,NCOMB),
	writeClause([NCOMB,MD]),
	createCombClauses(COMB,MDLS).

createCombinationVariable([],[],_).
createCombinationVariable([md-M-D|LS],[M|Res],D):-
	createCombinationVariable(LS,Res,D).

createCombinationVariableOpt([],[]).
createCombinationVariableOpt([M|LS],[M|Res]):-
	createCombinationVariableOpt(LS,Res).

negateBadCombinations(Comb,Rest):-
	pert(Var,Rest),
	negate(Var,NVar),
	negate(Comb,NComb),
	writeClause([NComb,NVar]),
	fail.
negateBadCombinations(_,_).

negateBadCombinationsOptimized(comb-R-D,Rest):-
	pert(M,Rest),
	negate(md-M-D,NVar),
	negate(comb-R-D,NComb),
	writeClause([NComb,NVar]),
	fail.
negateBadCombinationsOptimized(_,_).

createCombinationVariables([],[]).
createCombinationVariables([(L,Rest)|LS],[comb-R-D|RS]):-
	createCombinationVariable(L,R,D),
	findall(md-M-D,pert(M,R),Mds),
	createCombClauses(comb-R-D,Mds),
	negateBadCombinations(comb-R-D,Rest),
	% negateAll(L,NSubset),
	% pert(Var,Rest),
	% negate(Var,NVar),
	% writeClause([NVar|NSubset]),

	createCombinationVariables(LS,RS).

createCombinationVariablesOptimized([],[],_).
createCombinationVariablesOptimized([(L,Rest)|LS],[comb-R-D|RS],D):-
	createCombinationVariableOpt(L,R),
	findall(md-M-D,pert(M,R),Mds),
	createCombClauses(comb-R-D,Mds),
	negateBadCombinationsOptimized(comb-R-D,Rest),
	createCombinationVariablesOptimized(LS,RS,D).


symbolicOutput(0). % set to 1 to see symbolic output only; 0 otherwise.



day(D)					:- numDays(N), between(1,N,D).
zone(Z)					:- numDayZones(N), between(1,N,Z).
meal(M)					:- numMeals(N), between(1,N,M).
ingredient(I)			:- numIngredients(N), between(1,N,I).
mealOfZone(M,Z)			:- meal(M,_,_,_,LZ,_), member(Z,LZ).

getStatsMealAux(0,0,0,0,[],[]).
getStatsMealAux(Pres,Cres,Fres,Kres,[I|IS],[A|AS]):-
	component(I,_,_,KcalI,ProtI,CarbI,FatI,_,_,_,_),
	getStatsMealAux(Prot,Carbs,Fat,Kcal,IS,AS),
	Pres is Prot+ProtI*A,
	Cres is Carbs+CarbI*A,
	Fres is Fat+FatI*A,
	Kres is Kcal+KcalI*A.







listOfPert(_,[],[],[]).
listOfPert(Elem,[X|List],[X2|Result],Nopert):-
	pert_con_resto(Elem,X,X2),
	listOfPert(Elem,List,Result,Nopert),!.
listOfPert(Elem,[X|List],Result,[X|Nopert]):-
	listOfPert(Elem,List,Result,Nopert).


getStatsMeal(M,P,C,F,K):-
	meal(M,_,LI,LA,_,_),
	getStatsMealAux(P,C,F,K,LI,LA).


getStatsListMealsAux(0,0,0,0,[]).
getStatsListMealsAux(Pres,Cres,Fres,Kres,[md-M-_|MS]):-
	getStatsMeal(M,ProtI,CarbsI,FatI,KcalI),
	getStatsListMealsAux(Prot,Carbs,Fat,Kcal,MS),
	Pres is Prot+ProtI,
	Cres is Carbs+CarbsI,
	Fres is Fat+FatI,
	Kres is Kcal+KcalI.

getStatsListMealsAux2(P,C,F,K,[],P,C,F,K).
getStatsListMealsAux2(Prot,Carbs,Fat,Kcal,[md-M-_|MS],A1,A2,A3,A4):-
	getStatsMeal(M,ProtI,CarbsI,FatI,KcalI),
	Pres is Prot+ProtI,
	Cres is Carbs+CarbsI,
	Fres is Fat+FatI,
	Kres is Kcal+KcalI,
	numProtesDay(Plimit),
	numFatDay(Flimit),
	numCarbDay(Climit),
	numKcalDay(Klimit),
	marginStats(Margin),
	Margin > (Pres-Plimit)/Plimit*100,
	Margin > (Kres-Klimit)/Klimit*100,
	Margin > (Cres-Climit)/Climit*100,
	Margin > (Fres-Flimit)/Flimit*100,
	getStatsListMealsAux2(Pres,Cres,Fres,Kres,MS,A1,A2,A3,A4).

getStatsListMealsAux3(P,C,F,K,[],P,C,F,K).
getStatsListMealsAux3(Prot,Carbs,Fat,Kcal,[M|MS],A1,A2,A3,A4):-
	getStatsMeal(M,ProtI,CarbsI,FatI,KcalI),
	Pres is Prot+ProtI,
	Cres is Carbs+CarbsI,
	Fres is Fat+FatI,
	Kres is Kcal+KcalI,
	numProtesDay(Plimit),
	numFatDay(Flimit),
	numCarbDay(Climit),
	numKcalDay(Klimit),
	marginStats(Margin),
	Margin > (Pres-Plimit)/Plimit*100,
	Margin > (Kres-Klimit)/Klimit*100,
	Margin > (Cres-Climit)/Climit*100,
	Margin > (Fres-Flimit)/Flimit*100,
	getStatsListMealsAux3(Pres,Cres,Fres,Kres,MS,A1,A2,A3,A4).

getLimitedSubsets(Lits,Subset,Rest):-
	subset(Subset,Rest,Lits),
	getStatsListMealsAux(P,C,F,K,Subset),
	numProtesDay(Plimit),
	numFatDay(Flimit),
	numCarbDay(Climit),
	numKcalDay(Klimit),
	marginStats(Margin),
	Margin > abs(P-Plimit)/Plimit*100,
	Margin > abs(K-Klimit)/Klimit*100,
	Margin > abs(C-Climit)/Climit*100,
	Margin > abs(F-Flimit)/Flimit*100.

getLimitedSubsets2(Lits,Subset,Rest):-
	subset(Subset,Rest,Lits),
	getStatsListMealsAux2(0,0,0,0,Subset,P,C,F,K),
	numProtesDay(Plimit),
	numFatDay(Flimit),
	numCarbDay(Climit),
	numKcalDay(Klimit),
	marginStats(Margin),
	Margin > abs(P-Plimit)/Plimit*100,
	Margin > abs(K-Klimit)/Klimit*100,
	Margin > abs(C-Climit)/Climit*100,
	Margin > abs(F-Flimit)/Flimit*100.

getLimitedSubsets3(Lits,Subset,Rest):-
	subset(Subset,Rest,Lits),
	getStatsListMealsAux3(0,0,0,0,Subset,P,C,F,K),
	numProtesDay(Plimit),
	numFatDay(Flimit),
	numCarbDay(Climit),
	numKcalDay(Klimit),
	marginStats(Margin),
	Margin > abs(P-Plimit)/Plimit*100,
	Margin > abs(K-Klimit)/Klimit*100,
	Margin > abs(C-Climit)/Climit*100,
	Margin > abs(F-Flimit)/Flimit*100.


%%%%%%  Variables: It is mandatory to use AT LEAST these variables!

% mdz-M-D-Z
% md-M-D
% comb-R-D
%
writeClauses:-
	 oneMealPerZone,
	 mostMealPerZone,
	 limitMealOneDay,
	 limitMealAllDays,
	 noMealDayNoMealDayZone,
	% limitStatsDayCombinations,
	 limitStatsDayCombinationsOptimized,

    true.


mostMealPerZone:-
	day(D),
	zone(Z),
	Z is 5,
	findall(mdz-M-D-Z,mealOfZone(M,Z), Lits),
	atMost(1,Lits),
	fail.
mostMealPerZone:-
	day(D),
	zone(Z),
	Z is 3,
	findall(mdz-M-D-Z,mealOfZone(M,Z), Lits),
	atMost(1,Lits),
	fail.
mostMealPerZone:-
	limitMealsZone(Lim),
	day(D),
	zone(Z),
	findall(mdz-M-D-Z,mealOfZone(M,Z), Lits),
	atMost(Lim,Lits),
	fail.
mostMealPerZone.
oneMealPerZone:-
	day(D),
	zone(Z),
	findall(mdz-M-D-Z,mealOfZone(M,Z), Lits),
	atLeast(1,Lits),
	fail.
oneMealPerZone.

limitMealOneDay:-
	day(D),
	meal(M),
	findall(mdz-M-D-Z,zone(Z),Lits),
	atMost(1,Lits),
	fail.
limitMealOneDay.

limitMealAllDays:-
	meal(M),
	meal(M,_,_,_,_,[Min,Max]),
	findall(md-M-D,day(D),Lits),
	atMost(Max,Lits),
	fail.
limitMealAllDays.

noMealDayNoMealDayZone:-
    day(D),
    meal(M),
    findall(mdz-M-D-Z,mealOfZone(M,Z),Lits),
    expressOr(md-M-D, Lits),
    fail.
noMealDayNoMealDayZone.




limitStatsDayCombinations:-
	day(D),
	findall(md-M-D,meal(M),Lits),
	findall(
		(Subset,Rest),
		(
			getLimitedSubsets2(Lits,Subset,Rest)
		),
		Subsets),
	createCombinationVariables(Subsets, CombVars),
	exactly(1, CombVars),
	fail.
limitStatsDayCombinations.


limitStatsDayCombinationsOptimized:-
	findall(M,meal(M),Lits),
	findall(
		(Subset,Rest),
		(
			getLimitedSubsets3(Lits,Subset,Rest)
		),
		Subsets),
	day(D),
	createCombinationVariablesOptimized(Subsets, CombVars, D),
	exactly(1, CombVars),
	fail.
limitStatsDayCombinationsOptimized.

test(Len):-
	findall(M,meal(M),Lits),
	findall(
		(Subset,Rest),
		(
			getLimitedSubsets3(Lits,Subset,Rest)
		),
		Subsets),
	length(Subsets,Len),
	pert(([6,7,10,11,12,16,18],_),Subsets).











%%%%%%%%%%%%%%%%%%%%%%%
%%%%%% show the solution. Here M contains the literals that are true in the model:

displaySol(M):-write(M),nl,fail.
displaySol(M):-displaySchedule(M),fail.
displaySol(_).


%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Express that Var is equivalent to the disjunction of Lits:
expressOr( Var, Lits ):- member(Lit,Lits), negate(Lit,NLit), writeClause([ NLit, Var ]), fail.
expressOr( Var, Lits ):- negate(Var,NVar), writeClause([ NVar | Lits ]),!.


%%%%%% Cardinality constraints on arbitrary sets of literals Lits:

exactly(K,Lits):- atLeast(K,Lits), atMost(K,Lits),!.

atMost(K,Lits):-   % l1+...+ln <= k:  in all subsets of size k+1, at least one is false:
    negateAll(Lits,NLits),
    K1 is K+1,    subsetOfSize(K1,NLits,Clause), writeClause(Clause),fail.
atMost(_,_).

atLeast(K,Lits):-  % l1+...+ln >= k: in all subsets of size n-k+1, at least one is true:
    length(Lits,N),
    K1 is N-K+1,  subsetOfSize(K1, Lits,Clause), writeClause(Clause),fail.
atLeast(_,_).

negateAll( [], [] ).
negateAll( [Lit|Lits], [NLit|NLits] ):- negate(Lit,NLit), negateAll( Lits, NLits ),!.

negate(\+Lit,  Lit):-!.
negate(  Lit,\+Lit):-!.

subsetOfSize(0,_,[]):-!.
subsetOfSize(N,[X|L],[X|S]):- N1 is N-1, length(L,Leng), Leng>=N1, subsetOfSize(N1,L,S).
subsetOfSize(N,[_|L],   S ):-            length(L,Leng), Leng>=N,  subsetOfSize( N,L,S).


%%%%%% main:

main:-  symbolicOutput(1), !, writeClauses, halt.   % print the clauses in symbolic form and halt
main:-  initClauseGeneration,
        tell(clauses), writeClauses, told,          % generate the (numeric) SAT clauses and call the solver
	tell(header),  writeHeader,  told,
	numVars(N), numClauses(C),
	write('Generated '), write(C), write(' clauses over '), write(N), write(' variables. '),nl,
	shell('cat header clauses > infile.cnf',_),
	write('Calling solver....'), nl,
	shell('picosat -v -o model infile.cnf', Result),  % if sat: Result=10; if unsat: Result=20.
	treatResult(Result),!.

treatResult(20):- write('Unsatisfiable'), nl, halt.
treatResult(10):- write('Solution found: '), nl, see(model), symbolicModel(M), seen, displaySol(M), nl,nl,halt.

initClauseGeneration:-  %initialize all info about variables and clauses:
    retractall(numClauses(   _)),
    retractall(numVars(      _)),
    retractall(varNumber(_,_,_)),
    assert(numClauses( 0 )),
    assert(numVars(    0 )),     !.

writeClause([]):- symbolicOutput(1),!, nl.
writeClause([]):- countClause, write(0), nl.
writeClause([Lit|C]):- w(Lit), writeClause(C),!.
w( Lit ):- symbolicOutput(1), write(Lit), write(' '),!.
w(\+Var):- var2num(Var,N), write(-), write(N), write(' '),!.
w(  Var):- var2num(Var,N),           write(N), write(' '),!.


% given the symbolic variable V, find its variable number N in the SAT solver:
var2num(V,N):- hash_term(V,Key), existsOrCreate(V,Key,N),!.
existsOrCreate(V,Key,N):- varNumber(Key,V,N),!.                            % V already existed with num N
existsOrCreate(V,Key,N):- newVarNumber(N), assert(varNumber(Key,V,N)), !.  % otherwise, introduce new N for V

writeHeader:- numVars(N),numClauses(C), write('p cnf '),write(N), write(' '),write(C),nl.

countClause:-     retract( numClauses(N0) ), N is N0+1, assert( numClauses(N) ),!.
newVarNumber(N):- retract( numVars(   N0) ), N is N0+1, assert(    numVars(N) ),!.

% Getting the symbolic model M from the output file:
symbolicModel(M):- get_code(Char), readWord(Char,W), symbolicModel(M1), addIfPositiveInt(W,M1,M),!.
symbolicModel([]).
addIfPositiveInt(W,L,[Var|L]):- W = [C|_], between(48,57,C), number_codes(N,W), N>0, varNumber(_,Var,N),!.
addIfPositiveInt(_,L,L).
readWord( 99,W):- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ c
readWord(115,W):- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ s
readWord(-1,_):-!, fail. %end of file
readWord(C,[]):- member(C,[10,32]), !. % newline or white space marks end of word
readWord(Char,[Char|W]):- get_code(Char1), readWord(Char1,W), !.
%========================================================================================
