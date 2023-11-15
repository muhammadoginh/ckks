# OpenFHE Code Components

```mermaid
flowchart BT
    A[CORE<br/>- math implementation<br/>- lattice implementation<br/>- serialization] --> B[PKE<br/> -SIMD FHE];
    A --> C[BINFHE<br/>- binary FHE];
    B --> D[Application<br/>- encrypted data analysis<br/>- privacy-compliant data sharing];
    C --> D;
```

# binFHE

    -[ ] Boolean arithmetic, comparisons, and aribtrary function evaluation based on Ducas-Micciancio (DM) and Chillotti-Gama-Georgieva-Izabachene (CGGI) schemes

# core

- underlying implementation providing the base that `binFHE` and `pke` are built off of

# pke

    -[x] real-number arithmetic based on Cheon-Kim-Kim-Song (CKKS) scheme
    -[ ] integer arithmetic based on Brakerski-Gentry-Vaikuntanathan (BGV) and Brakerski/Fan-Vercauteren (BFV) schemes