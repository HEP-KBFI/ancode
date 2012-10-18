from ROOT import TH1D,TFile

f=TFile('out.root')
cf=f.Get("stfilt/cflow")
for i in range(1,8):
    print "Step",i-1,"->",cf.GetBinContent(i)

