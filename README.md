# SHA3


## Pseudo-code for SHA3 implementation

```
SHA3(family):
    PARAMETRES :
        - output_length                          # output length in bits (224, 256, 384, 512) (l)
        - state_size = 1600                      # total size of state in bits (s)
        - rate = state_size - 2 * output_length  # rate (r = s - 2*l)
        - capacity = state_size - rate           # capacity (c = s - r)
        - rounds = 24                            # number of Keccak rounds

    Initiate the `state` array to 0 (1600 bits)
    RETURN SHA3_instance(rate, capacity, output_length, state, rounds)
```

```
SHA3_Instance(rate, capacity, output_length, state, rounds):
    METHODS :
        Absorb(message):
            - Add padding to the message according to `rate`
            - Divide the message into blocks of size `rate` bits
            - For each block :
                - XOR the block with the corresponding part of the `state`
                - Apply keccak_f(state, rounds)
        
        Squeeze():
            - Initiate output = []
            - While output_length > current_size(output):
                - Add the first `rate` bits of the state to output
                - If output_length > current_size(output):
                    - Apply keccak_f(state, rounds)
            - RETURN `output_length` bits

        Compute(message):
            Absorb(message)
            RETURN Squeeze()
```

```
Padding(message, rate):
    - Add one bit 1 to the end of the message
    - Complete the message with bits 0 until the message size is a multiple of `rate` bits
    - Replace the last bit of the last block with a bit 1
    - RETURN the padded message
```

```
keccak_f(state, rounds):
    FOR each round from 0 to rounds-1 :
        - state = θ(state)
        - state = ρ(state)
        - state = π(state)
        - state = χ(state)
        - state = ι(state, round_index)
    RETURN state
```

```
θ(state):
    # Initialize a parity array for each column
    C[x] = XOR(state[x, 0], state[x, 1], state[x, 2], state[x, 3], state[x, 4]) for x = 0 to 4

    # Compute offsets for inter-column correction
    D[x] = C[x-1] XOR ROTATE_LEFT(C[x+1], 1) for x = 0 to 4

    # Update each lane of status
    FOR x = 0 to 4:
        FOR y = 0 to 4:
            state[x, y] = state[x, y] XOR D[x]

    RETURN state
------------------------------------------------------------
ρ(state):
    # Initial rotation for position (0, 0) (no rotation here)
    offsets[x, y] = Fixed values defined by Keccak specifications

    FOR x = 0 to 4:
        FOR y = 0 to 4:
            # Apply a circular rotation of 'offsets[x, y]' bits to the lane
            state[x, y] = ROTATE_LEFT(state[x, y], offsets[x, y])

    RETURN state
------------------------------------------------------------
π(state):
    # Create a copy of the state
    temp_state = Copy_of(state)

    FOR x = 0 to 4:
        FOR y = 0 to 4:
            # Move each lane to a new position
            new_x = y
            new_y = (2 * x + 3 * y) mod 5
            state[new_x, new_y] = temp_state[x, y]

    RETURN state
------------------------------------------------------------
χ(state):
    FOR y = 0 to 4:
        # Create a temporary copy of the line
        temp_row = [state[x, y] for x = 0 to 4]

        FOR x = 0 to 4:
            # Modify the lane according to the bits of neighboring lanes
            state[x, y] = temp_row[x] XOR ((NOT temp_row[(x+1) mod 5]) AND temp_row[(x+2) mod 5])

    RETURN state
------------------------------------------------------------
ι(state, round_index):
    # RC constants defined in the Keccak specification
    RC[round_index] = Specific fixed values for each round

    # XOR round constant with lane (0, 0)
    state[0, 0] = state[0, 0] XOR RC[round_index]

    RETURN state
------------------------------------------------------------
RC[] = 
{
    0x0000000000000001L, 0x0000000000008082L, 0x800000000000808aL,
    0x8000000080008000L, 0x000000000000808bL, 0x0000000080000001L,
    0x8000000080008081L, 0x8000000000008009L, 0x000000000000008aL,
    0x0000000000000088L, 0x0000000080008009L, 0x000000008000000aL,
    0x000000008000808bL, 0x800000000000008bL, 0x8000000000008089L,
    0x8000000000008003L, 0x8000000000008002L, 0x8000000000000080L,
    0x000000000000800aL, 0x800000008000000aL, 0x8000000080008081L,
    0x8000000000008080L, 0x0000000080000001L, 0x8000000080008008L
};
```

```
Main():
    - Read input file or binary data
    - Select SHA3 family (224, 256, 384, 512)
    - Initialize SHA3_instance with family parameters
    - Call Compute(message) to calculate hash
    - Display result in hexadecimal form
```