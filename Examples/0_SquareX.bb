assign X 7;
export X;

clear Z;
clear N;
clear M;
while X not 0 do;
  incr N;
  incr M;
  decr X;
end;
while M not 0 do;
  clear P;
  while N not 0 do;
    incr Z;
    incr P;
    decr N;
  end;
  while P not 0 do;
    incr N;
    decr P;
  end;
  decr M;
end;

export Z;


