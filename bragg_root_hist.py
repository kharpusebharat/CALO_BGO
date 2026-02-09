#!/usr/bin/env python3
import sys
import ROOT

# --- User settings ---
INPUT_ROOT = "/home/bharat/Documents/geant4/CALO/build/brag_C2_100.root"
BIN_WIDTH_MM = 0.1     # 1 mm bins
N_EVENTS = 0           # 0 = auto-detect from eventID
OUTPUT_ROOT = "brag_C2_100_hist.root"
# ---------------------

f = ROOT.TFile.Open(INPUT_ROOT)
if not f or f.IsZombie():
    raise RuntimeError(f"Cannot open {INPUT_ROOT}")

te = f.Get("BraggEvent")
tr = f.Get("BraggRun")
if not te and not tr:
    raise RuntimeError("Neither TTree 'BraggEvent' nor 'BraggRun' found")

def make_hist(tree, name, zmin, zmax):
    nbins = int((zmax - zmin) / BIN_WIDTH_MM) + 1
    h = ROOT.TH1D(name, "Bragg Curve;Depth z (mm);Edep per event (MeV)",
                  nbins, zmin, zmin + nbins * BIN_WIDTH_MM)
    tree.Draw(f"z>>{name}", "edep", "goff")
    return h

# Set explicit axis range (mm)
Z_MIN_MM = 0.0
Z_MAX_MM = 100.0

h_event = None
if te:
    h_event = make_hist(te, "hBraggEvent", Z_MIN_MM, Z_MAX_MM)
    if N_EVENTS <= 0:
        unique_ids = set()
        for entry in te:
            unique_ids.add(int(entry.eventID))
        N_EVENTS = len(unique_ids)
    if N_EVENTS > 0:
        h_event.Scale(1.0 / N_EVENTS)

h_run = None
if tr:
    h_run = make_hist(tr, "hBraggRun", Z_MIN_MM, Z_MAX_MM)
    if N_EVENTS > 0:
        h_run.Scale(1.0 / N_EVENTS)

out = ROOT.TFile.Open(OUTPUT_ROOT, "RECREATE")
if h_event:
    h_event.Write()
if h_run:
    h_run.Write()
out.Close()

print(f"Wrote histograms to {OUTPUT_ROOT}")
