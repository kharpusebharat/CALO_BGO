# CALO_BGO

Beam simulation in BGO to study crystal response and Bragg curves for light ions over different energy ranges.

<img width="868" height="388" alt="Screenshot from 2026-02-11 23-08-12" src="https://github.com/user-attachments/assets/f630dbc5-3250-4356-bc75-99c35514b212" />


**Features**
- Tapered BGO crystal (2x2 cm front, 2.8x2.8 cm back, 24 cm length)
- SiPM tile on the back face with 5x5 macro-cells
- Bragg curve scoring with configurable Z bin size
- ROOT output (`output*.root`)

**Build**
```
cmake -S . -B build
cmake --build build
```

**Run**
1. Source Geant4 environment:
```
. geant4make.sh
```
2. Run the simulation:
```
./build/sim
```
3. Run with macro:
```
./build/sim score.mac
```

**Output**
- `output*.root` contains ROOT trees.
- `BraggRun` holds run-level binned energy deposition vs Z.

**Notes**
- For ion beams, set particle and energy in macros.
- Use `score.mac` to configure scoring mesh or beam settings.
