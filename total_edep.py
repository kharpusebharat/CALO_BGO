#!/usr/bin/env python3
import ROOT

INPUT_ROOT = "/home/bharat/Documents/geant4/CALO/build/brag_C2_200.root"
TREE_NAME = "BraggRun"   # use BraggRun for per-run bins
N_EVENTS = 500000        # set to your run statistics

f = ROOT.TFile.Open(INPUT_ROOT)
if not f or f.IsZombie():
    raise RuntimeError(f"Cannot open {INPUT_ROOT}")

t = f.Get(TREE_NAME)
if not t:
    raise RuntimeError(f"TTree '{TREE_NAME}' not found")

# Sum edep over all z bins
edep_total = 0.0
for entry in t:
    edep_total += entry.edep

print(f"Total deposited energy (sum over bins) = {edep_total} MeV")
if N_EVENTS > 0:
    print(f"Per-event deposited energy = {edep_total / N_EVENTS} MeV")
