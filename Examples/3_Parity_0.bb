assign X 7;
export X;

clear Z;
while X not 0 do;
  invert Z;
  decr X;
end;

export Z;
