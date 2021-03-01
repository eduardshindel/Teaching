/*
1.18. ������� �� ������ �� ������ ���������� X ���� �������, ���� ����� ������� �
������� �� X.
��������, [1,8,2,1,1,5,1], X=1-> [1,2,1,1,1].
*/

del_afterX :-
    read(L),
    read(X),
    del(L, X, L1),
    writeln(L1).

del([], _, []).
del([X, K | L], X, [X | L1]):-
    K \= X,
    !,
    del(L, X, L1).
del([H | L], X, [H | L1]):-
    del(L, X, L1).


/*
2.18. ������� �� ���������� �����, ���������� �� ���������� �����, ��� �������������
����� � ������ �������, �������� ������� �����. ����������� ����� ����.
*/

walk(_, []):-
    at_end_of_stream,
    !.

walk(F, [H|T]):-
    read_line_to_codes(F, COD),
    string_codes(H, COD),
    walk(F, T).

out(_, []):- !.

out(R,[H|T]):-
    writeln(H),
    out(R, T).

del_one([],[]):- !.
del_one([H|T], [NH|List]):-
    string_chars(H,H1),
    length(H1, X),
    (X =:= 1 -> delete(H1,NH,NH),del_one(T, List);
    string_chars(NH,H1),
    del_one(T, List)).

del_space([],[]):- !.
del_space([H|T],[NH|List]):-
    string_chars(H,H1),
    delete(H1,' ',H2),
    string_chars(NH,H2),
    del_space(T,List).
    
     
del_str:-
    write('������� ��� �������� �����:'), read(R),
    open(R,read,S1),
    set_input(S1),
    walk(S1,L),
    close(S1),
    del_one(L1,L2),
    del_space(L,L1),
    delete(L2,[],LS),
    write('������� ��� ��������� �����:'),read(O),
    (exists_file(O),delete_file(O), !; true),
    open(O,write,S2),
    set_output(S2),
    out(S2,LS),
    close(S2).


/*
3.18. �������� ���� ������ � �������� ��� ���������� �� �������: ������ �������,
������ �������, ���� ����. ���������� ��� �������, ������������ ����������
���������� ����� (�� ���� ���������).
*/

start:-
    retractall(info/4),
    reconsult('info1.pl'),
    retractall(losers/3),
    reconsult('losers.pl'),
    dynamic(info/4),
    menu.


menu:-
    write('���� ������ "���������"'),nl,
    write('1- �������� ���� ������'),nl,
    write('2- ���������� ����� �������'),nl,
    write('3- �������� ������ �� ���� ������'),nl,
    write('4- �������������� ������ ���� ������'),nl,
    write('5- ����� ���������� � ���� ������'),nl,
    write('�������� ����� ����: (1-5)'),nl,
    read(X),
    X<6,
    process(X),
    db_save_info.

process(1):-view_info.
process(2):-add_info,!.
process(3):-remove_info,!.
process(4):-mody_info,!.
process(5):-find_info.

view_info :-
    info(Num,T1,T2,Score),
    write('����� ������: '), write(Num),nl,
    write('������ �������: '), write(T1),nl,
    write('������ �������: '),write(T2),nl,
    write('����: '),write(Score),nl,
    write('------------------------------------------------------'),nl,
    fail.
view_info.

add_info:-
    write('�������� ����: '),nl,nl,
    repeat,
    write('����� ������: '),read(Num),nl,
    write('������ �������: '),read(T1),nl,
    write('������ �������: '),read(T2),nl,
    write('����: '),read(Score),nl,
    assertz(info(Num,T1,T2,Score)),
    quest,!.

quest:-
    write('�������� ��� ���� ����? y/n '),
    read(A),
    answer(A).

answer(""):-fail.
answer(y):-fail.
answer(n).

db_save_info:-
    tell('info1.pl'),
    listing(info/4),
    told,
    tell('losers.pl'),
    listing(losers/3),
    told,
    write('���� ���� ������ ��������!').

remove_info:-
    write('������� ����� �����, ������� ������ �������'),
    read(Num),
    retract(info(Num,_,_,_)),
    write('���� ������!').

mody_info:-
    write('������� ����� ������, ������� ������ ���������������: '),
    read(Num),nl,
    info(Num,T1,T2,Score),
    write('���� ������'),nl,
    write('------------------------------------------------------'),nl,
    write('����� ������: '), write(Num),nl,
    write('������ �������: '), write(T1),nl,
    write('������ �������: '),write(T2),nl,
    write('����: '),write(Score),nl,
    write('------------------------------------------------------'),nl,
    write('::::�������������� ���� �� ������::::'),nl,
    write('1- ���� ������'),nl,
    write('2- ���� ������ �������'),nl,
    write('3- ���� ������ �������'),nl,
    write('4- ���� �����'),nl,

    write('����� ���� ������ ���������������?'),nl,
    read(Pole),
    red(Pole,Num),
    db_save_info.

red(1,Num):-write('������� ����� ����� ������: '),
    read(NewNum),
    info(Num,T1,T2,Score),
    A = T1,
    B = T2,
    C = Score,
    retract(info(Num,_,_,_)),
    asserta(info(NewNum,A,B,C)).

red(2,Num):-write('������� ����� �������� ������ �������: '),
    read(NT1),
    info(Num,_,T2,Score),
    A = NT1,
    B = T2,
    C = Score,
    retract(info(Num,_,_,_)),
    asserta(info(NewNum,A,B,C)).

red(3,Num):-write('������� ����� �������� ������ �������: '),
    read(NT2),
    info(Num,T1,_,Score),
    A = T1,
    B = NT2,
    C = Score,
    retract(info(Num,_,_,_)),
    asserta(info(NewNum,A,B,C)).

red(4,Num):-write('������� ����� ����: '),
    read(NScore),
    info(Num,T1,T2,_),
    A = T1,
    B = T2,
    C = NScore,
    retract(info(Num,_,_,_)),
    asserta(info(NewNum,A,B,C)).

find_info:-
    write('����� ������ � ���������� ����������� ����������� �����'),nl,
    find_loser,
    max_goal.

max_goal:-
    findall(X,losers(Num,T,X),Digits),max_list(Digits,Max),
    losers(Num,T,X),
    retract(losers(Num,T,X)),
    delete(Digits, Max, Nmax),
    max_list(Nmax,Y),
    (X > Y -> write(T), write(' ����������: '),write(X),nl),
    fail.
max_goal.

find_loser :-
    info(Num,T1,T2,Score),
    split_string(Score,':',"",Ls),
    splite(Ls,Ls1,Ls2),
    convert(Ls1,L1,Sc1),
    convert(Ls2,L2,Sc2),
    (Sc1 > Sc2 -> assertz(losers(Num,T2,Sc1));
    Sc2 > Sc1 -> assertz(losers(Num,T1,Sc2));
    assertz(losers(Num,T1,Sc2)), assertz(losers(Num,T2,Sc1))),
    fail.
find_loser.

splite([],[],[]).
splite([H|T],[H],T):-!.

convert([],[],_).
convert([H|T],[Eh|Et],X):-
    string_to_atom(H,Eh),
    atom_number(Eh,X).