assign N 7;
export N;

clear Z;
while N not 0 do;
  clear M;
  while N not 0 do;
    incr M;
    decr N;
  end;
  while M not 0 do;
    incr Z;
    incr N;
    decr M;
  end;
  decr N;
end;

export Z;
