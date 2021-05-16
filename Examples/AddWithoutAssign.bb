clear X;
incr X;
incr X;
incr X;
incr X;

clear Z;
while X not 0 do;
    incr Z;
    decr X;
end;
while Y not 0 do;
    incr Z;
    decr Y;
end;
export Z;
