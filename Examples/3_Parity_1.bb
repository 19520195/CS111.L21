assign X 7;
export X;

clear Z;
while X not 0 do;
  incr Z;
  decr X;
  clear cX;
  while X not 0 do;
    incr cX;
    decr X;
  end;
  while cX not 0 do;
    clear Z;
    incr X;
    decr cX;
  end;
  decr X;
end;

export Z;
