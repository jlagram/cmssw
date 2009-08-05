#ifndef FOURVECTORHLTOFFLINE_H
#define FOURVECTORHLTOFFLINE_H
// -*- C++ -*-
//
// Package:    FourVectorHLTOffline
// Class:      FourVectorHLTOffline
// 
/**\class FourVectorHLTOffline FourVectorHLTOffline.cc 

 Description: This is a DQM source meant to plot high-level HLT trigger
 quantities as stored in the HLT results object TriggerResults

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Jeffrey Berryhill
//         Created:  June 2008
// Rewritten by: Vladimir Rekovic
//         Date:  May 2009
//
// $Id: FourVectorHLTOffline.h,v 1.26 2009/07/10 01:16:37 rekovic Exp $
//
//

// system include files
#include <memory>
#include <unistd.h>


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// added VR
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "FWCore/Framework/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/TauReco/interface/CaloTauFwd.h"
#include "DataFormats/TauReco/interface/CaloTau.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
/* MC
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "DataFormats/METReco/interface/GenMET.h"
*/
#include "DataFormats/Math/interface/deltaR.h"
#include  "DataFormats/HLTReco/interface/TriggerTypeDefs.h"

#include "DQMServices/Core/interface/MonitorElement.h"


#include "DataFormats/HLTReco/interface/TriggerEventWithRefs.h"
#include "DataFormats/JetReco/interface/JetFloatAssociation.h"


#include <iostream>
#include <fstream>
#include <vector>


typedef std::multimap<float,int> fimmap ;
typedef std::set<fimmap , less<fimmap> > mmset;

class FourVectorHLTOffline : public edm::EDAnalyzer {
   public:
      explicit FourVectorHLTOffline(const edm::ParameterSet&);
      ~FourVectorHLTOffline();

      void cleanDRMatchSet(mmset& tempSet);

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // BeginRun
      void beginRun(const edm::Run& run, const edm::EventSetup& c);

      // EndRun
      void endRun(const edm::Run& run, const edm::EventSetup& c);


      // ----------member data --------------------------- 
      int nev_;
      DQMStore * dbe_;

      MonitorElement* total_;

      bool plotAll_;
      bool resetMe_;
      int currentRun_;
 
      unsigned int nBins_; 
      double ptMin_ ;
      double ptMax_ ;
      
      double electronEtaMax_;
      double electronEtMin_;
      double electronDRMatch_;
      double muonEtaMax_;
      double muonEtMin_;
      double muonDRMatch_;
      double tauEtaMax_;
      double tauEtMin_;
      double tauDRMatch_;
      double jetEtaMax_;
      double jetEtMin_;
      double jetDRMatch_;
      double bjetEtaMax_;
      double bjetEtMin_;
      double bjetDRMatch_;
      double photonEtaMax_;
      double photonEtMin_;
      double photonDRMatch_;
      double trackEtaMax_;
      double trackEtMin_;
      double trackDRMatch_;
      double metEtaMax_;
      double metMin_;
      double metDRMatch_;
      double htEtaMax_;
      double htMin_;
      double htDRMatch_;
      double sumEtMin_;

      std::vector<std::pair<std::string, std::string> > custompathnamepairs_;


      std::string dirname_;
      std::string processname_;
      bool monitorDaemon_;
      int theHLTOutputType;
      edm::InputTag triggerSummaryLabel_;
      edm::InputTag triggerResultsLabel_;
      HLTConfigProvider hltConfig_;
      // data across paths
      MonitorElement* scalersSelect;
      // helper class to store the data path

      class PathInfo {
	PathInfo():
	  pathIndex_(-1), denomPathName_("unset"), pathName_("unset"), l1pathName_("unset"), filterName_("unset"), processName_("unset"), objectType_(-1)
	  {};
      public:
	void setHistos(
                       MonitorElement* const NOn, 
                       MonitorElement* const onEtOn, 
                       MonitorElement* const onEtavsonPhiOn,  
                       MonitorElement* const NOff, 
                       MonitorElement* const offEtOff, 
                       MonitorElement* const offEtavsoffPhiOff,
                       MonitorElement* const NL1, 
                       MonitorElement* const l1EtL1, 
		       MonitorElement* const l1Etavsl1PhiL1,
                       MonitorElement* const NL1On, 
                       MonitorElement* const l1EtL1On, 
		       MonitorElement* const l1Etavsl1PhiL1On,
                       MonitorElement* const NL1Off,   
                       MonitorElement* const offEtL1Off, 
		       MonitorElement* const offEtavsoffPhiL1Off,
                       MonitorElement* const NOnOff, 
                       MonitorElement* const offEtOnOff, 
		       MonitorElement* const offEtavsoffPhiOnOff,
                       MonitorElement* const NL1OnUM, 
                       MonitorElement* const l1EtL1OnUM, 
		       MonitorElement* const l1Etavsl1PhiL1OnUM,
                       MonitorElement* const NL1OffUM,   
                       MonitorElement* const offEtL1OffUM, 
		       MonitorElement* const offEtavsoffPhiL1OffUM,
                       MonitorElement* const NOnOffUM, 
                       MonitorElement* const offEtOnOffUM, 
		       MonitorElement* const offEtavsoffPhiOnOffUM,
                       MonitorElement* const offDRL1Off, 
                       MonitorElement* const offDROnOff, 
                       MonitorElement* const l1DRL1On 
					 ) {
          NOn_ = NOn;
	  onEtOn_ = onEtOn;
	  onEtavsonPhiOn_ = onEtavsonPhiOn;
          NOff_ = NOff;
	  offEtOff_ = offEtOff;
	  offEtavsoffPhiOff_ = offEtavsoffPhiOff;
          NL1_ = NL1;
	  l1EtL1_ = l1EtL1;
	  l1Etavsl1PhiL1_ = l1Etavsl1PhiL1;
          NL1On_ = NL1On;
	  l1EtL1On_ = l1EtL1On;
	  l1Etavsl1PhiL1On_ = l1Etavsl1PhiL1On;
          NL1Off_ = NL1Off;
	  offEtL1Off_ = offEtL1Off;
	  offEtavsoffPhiL1Off_ = offEtavsoffPhiL1Off;
          NOnOff_ = NOnOff;
	  offEtOnOff_ = offEtOnOff;
	  offEtavsoffPhiOnOff_ = offEtavsoffPhiOnOff;
          NL1OnUM_ = NL1OnUM;
	  l1EtL1OnUM_ = l1EtL1OnUM;
	  l1Etavsl1PhiL1OnUM_ = l1Etavsl1PhiL1OnUM;
          NL1OffUM_ = NL1OffUM;
	  offEtL1OffUM_ = offEtL1OffUM;
	  offEtavsoffPhiL1OffUM_ = offEtavsoffPhiL1OffUM;
          NOnOffUM_ = NOnOffUM;
	  offEtOnOffUM_ = offEtOnOffUM;
	  offEtavsoffPhiOnOffUM_ = offEtavsoffPhiOnOffUM;
    offDRL1Off_ =  offDRL1Off; 
    offDROnOff_ =  offDROnOff; 
    l1DRL1On_   =  l1DRL1On;
	}
	MonitorElement * getNOnHisto() {
	  return NOn_;
	}
	MonitorElement * getOnEtOnHisto() {
	  return onEtOn_;
	}
	MonitorElement * getOnEtaVsOnPhiOnHisto() {
	  return onEtavsonPhiOn_;
	}
	MonitorElement * getNOffHisto() {
	  return NOff_;
	}
	MonitorElement * getOffEtOffHisto() {
	  return offEtOff_;
	}
	MonitorElement * getOffEtaVsOffPhiOffHisto() {
	  return offEtavsoffPhiOff_;
	}
	MonitorElement * getNL1Histo() {
	  return NL1_;
	}
	MonitorElement * getL1EtL1Histo() {
	  return l1EtL1_;
	}
	MonitorElement * getL1EtaVsL1PhiL1Histo() {
	  return l1Etavsl1PhiL1_;
	}
	MonitorElement * getNL1OnHisto() {
	  return NL1On_;
	}
	MonitorElement * getL1EtL1OnHisto() {
	  return l1EtL1On_;
	}
	MonitorElement * getL1EtaVsL1PhiL1OnHisto() {
	  return l1Etavsl1PhiL1On_;
	}
	MonitorElement * getNL1OffHisto() {
	  return NL1Off_;
	}
	MonitorElement * getOffEtL1OffHisto() {
	  return offEtL1Off_;
	}
	MonitorElement * getOffEtaVsOffPhiL1OffHisto() {
	  return offEtavsoffPhiL1Off_;
	}
	MonitorElement * getNOnOffHisto() {
	  return NOnOff_;
	}
	MonitorElement * getOffEtOnOffHisto() {
	  return offEtOnOff_;
	}
	MonitorElement * getOffEtaVsOffPhiOnOffHisto() {
	  return offEtavsoffPhiOnOff_;
	}


	MonitorElement * getNL1OnUMHisto() {
	  return NL1OnUM_;
	}
	MonitorElement * getL1EtL1OnUMHisto() {
	  return l1EtL1OnUM_;
	}
	MonitorElement * getL1EtaVsL1PhiL1OnUMHisto() {
	  return l1Etavsl1PhiL1OnUM_;
	}
	MonitorElement * getNL1OffUMHisto() {
	  return NL1OffUM_;
	}
	MonitorElement * getOffEtL1OffUMHisto() {
	  return offEtL1OffUM_;
	}
	MonitorElement * getOffEtaVsOffPhiL1OffUMHisto() {
	  return offEtavsoffPhiL1OffUM_;
	}
	MonitorElement * getNOnOffUMHisto() {
	  return NOnOffUM_;
	}
	MonitorElement * getOffEtOnOffUMHisto() {
	  return offEtOnOffUM_;
	}
	MonitorElement * getOffEtaVsOffPhiOnOffUMHisto() {
	  return offEtavsoffPhiOnOffUM_;
	}


	MonitorElement * getOffDRL1OffHisto() {
	  return offDRL1Off_;
	}
	MonitorElement * getOffDROnOffHisto() {
	  return offDROnOff_;
	}
	MonitorElement * getL1DROnL1Histo() {
	  return l1DRL1On_;
	}
	const std::string getLabel(void ) const {
	  return filterName_;
	}
	void setLabel(std::string labelName){
	  filterName_ = labelName;
          return;
	}
	const std::string getPath(void ) const {
	  return pathName_;
	}
	const std::string getl1Path(void ) const {
	  return l1pathName_;
	}
	const std::string getDenomPath(void ) const {
	  return denomPathName_;
	}
	const std::string getProcess(void ) const {
	  return processName_;
	}
	const int getObjectType(void ) const {
	  return objectType_;
	}

        const edm::InputTag getTag(void) const{
	  edm::InputTag tagName(filterName_,"",processName_);
          return tagName;
	}
	~PathInfo() {};
	PathInfo(std::string denomPathName, std::string pathName, std::string l1pathName, std::string filterName, std::string processName, size_t type, float ptmin, 
		 float ptmax):
	  denomPathName_(denomPathName), pathName_(pathName), l1pathName_(l1pathName), filterName_(filterName), processName_(processName), objectType_(type),
          NOn_(0), onEtOn_(0), onEtavsonPhiOn_(0),
	  NOff_(0), offEtOff_(0), offEtavsoffPhiOff_(0),
	  NL1_(0), l1EtL1_(0), l1Etavsl1PhiL1_(0),
          NL1On_(0), l1EtL1On_(0), l1Etavsl1PhiL1On_(0),
	  NL1Off_(0), offEtL1Off_(0), offEtavsoffPhiL1Off_(0),
	  NOnOff_(0), offEtOnOff_(0), offEtavsoffPhiOnOff_(0),
          NL1OnUM_(0), l1EtL1OnUM_(0), l1Etavsl1PhiL1OnUM_(0),
	  NL1OffUM_(0), offEtL1OffUM_(0), offEtavsoffPhiL1OffUM_(0),
	  NOnOffUM_(0), offEtOnOffUM_(0), offEtavsoffPhiOnOffUM_(0),
		offDRL1Off_(0), offDROnOff_(0), l1DRL1On_(0),
	  ptmin_(ptmin), ptmax_(ptmax)
	  {
	  };
	  PathInfo(std::string denomPathName, std::string pathName, std::string l1pathName, std::string filterName, std::string processName, size_t type,
		   MonitorElement *NOn,
		   MonitorElement *onEtOn,
		   MonitorElement *onEtavsonPhiOn,
		   MonitorElement *NOff,
		   MonitorElement *offEtOff,
		   MonitorElement *offEtavsoffPhiOff,
		   MonitorElement *NL1,
		   MonitorElement *l1EtL1,
		   MonitorElement *l1Etavsl1PhiL1,
		   MonitorElement *NL1On,
		   MonitorElement *l1EtL1On,
		   MonitorElement *l1Etavsl1PhiL1On,
		   MonitorElement *NL1Off,
		   MonitorElement *offEtL1Off,
		   MonitorElement *offEtavsoffPhiL1Off,
		   MonitorElement *NOnOff,
		   MonitorElement *offEtOnOff,
		   MonitorElement *offEtavsoffPhiOnOff,
		   MonitorElement *NL1OnUM,
		   MonitorElement *l1EtL1OnUM,
		   MonitorElement *l1Etavsl1PhiL1OnUM,
		   MonitorElement *NL1OffUM,
		   MonitorElement *offEtL1OffUM,
		   MonitorElement *offEtavsoffPhiL1OffUM,
		   MonitorElement *NOnOffUM,
		   MonitorElement *offEtOnOffUM,
		   MonitorElement *offEtavsoffPhiOnOffUM,
       MonitorElement *offDRL1Off, 
       MonitorElement *offDROnOff, 
       MonitorElement *l1DRL1On,
		   float ptmin, float ptmax
		   ):
	    denomPathName_(denomPathName), pathName_(pathName), l1pathName_(l1pathName), filterName_(filterName), processName_(processName), objectType_(type),
            NOn_(NOn), onEtOn_(onEtOn), onEtavsonPhiOn_(onEtavsonPhiOn),
	    NOff_(NOff), offEtOff_(offEtOff), offEtavsoffPhiOff_(offEtavsoffPhiOff),
	    NL1_(NL1), l1EtL1_(l1EtL1), l1Etavsl1PhiL1_(l1Etavsl1PhiL1),
            NL1On_(NL1On), l1EtL1On_(l1EtL1On), l1Etavsl1PhiL1On_(l1Etavsl1PhiL1On),
	    NL1Off_(NL1Off), offEtL1Off_(offEtL1Off), offEtavsoffPhiL1Off_(offEtavsoffPhiL1Off),
	    NOnOff_(NOnOff), offEtOnOff_(offEtOnOff), offEtavsoffPhiOnOff_(offEtavsoffPhiOnOff),
            NL1OnUM_(NL1OnUM), l1EtL1OnUM_(l1EtL1OnUM), l1Etavsl1PhiL1OnUM_(l1Etavsl1PhiL1OnUM),
	    NL1OffUM_(NL1OffUM), offEtL1OffUM_(offEtL1OffUM), offEtavsoffPhiL1OffUM_(offEtavsoffPhiL1OffUM),
	    NOnOffUM_(NOnOffUM), offEtOnOffUM_(offEtOnOffUM), offEtavsoffPhiOnOffUM_(offEtavsoffPhiOnOffUM),
    offDRL1Off_(offDRL1Off), 
    offDROnOff_(offDROnOff), 
    l1DRL1On_(l1DRL1On),
	    ptmin_(ptmin), ptmax_(ptmax)
	    {};
	    bool operator==(const std::string v) 
	    {
	      return v==filterName_;
	    }
      private:
	  int pathIndex_;
	  std::string denomPathName_;
	  std::string pathName_;
	  std::string l1pathName_;
	  std::string filterName_;
	  std::string processName_;
	  int objectType_;

	  // we don't own this data
    MonitorElement *NOn_, *onEtOn_, *onEtavsonPhiOn_;
	  MonitorElement *NOff_, *offEtOff_, *offEtavsoffPhiOff_;
	  MonitorElement *NL1_, *l1EtL1_, *l1Etavsl1PhiL1_;
	  MonitorElement *NL1On_, *l1EtL1On_, *l1Etavsl1PhiL1On_;
	  MonitorElement *NL1Off_, *offEtL1Off_, *offEtavsoffPhiL1Off_;
	  MonitorElement *NOnOff_, *offEtOnOff_, *offEtavsoffPhiOnOff_;
	  MonitorElement *NL1OnUM_, *l1EtL1OnUM_, *l1Etavsl1PhiL1OnUM_;
	  MonitorElement *NL1OffUM_, *offEtL1OffUM_, *offEtavsoffPhiL1OffUM_;
	  MonitorElement *NOnOffUM_, *offEtOnOffUM_, *offEtavsoffPhiOnOffUM_;
    MonitorElement *offDRL1Off_, *offDROnOff_, *l1DRL1On_;

	  float ptmin_, ptmax_;

	  const int index() { 
	    return pathIndex_;
	  }
	  const int type() { 
	    return objectType_;
	  }
      public:
	  float getPtMin() const { return ptmin_; }
	  float getPtMax() const { return ptmax_; }
      };

      // simple collection - just 
      class PathInfoCollection: public std::vector<PathInfo> {
      public:
	PathInfoCollection(): std::vector<PathInfo>() 
	  {};
	  std::vector<PathInfo>::iterator find(std::string pathName) {
	    return std::find(begin(), end(), pathName);
	  }
      };
      PathInfoCollection hltPaths_;


};

template <class T> 
class objMonData {
public:
    objMonData() { EtaMax_= 2.5; EtMin_=3.0; GenJetsFlag_ = false; BJetsFlag_ = false; }
		void setLimits(float etaMax, float etMin, float drMatch) 
		{
		 EtaMax_= etaMax; 
		 EtMin_= etMin; 
		 DRMatch_= drMatch;
		}
		void setTriggerType(std::vector<int> trigType) { triggerType_ = trigType; }
		void pushTriggerType(int trigType) { triggerType_.push_back(trigType); }
		void setL1TriggerType(std::vector<int> trigType) { l1triggerType_ = trigType; }
		void pushL1TriggerType(int trigType) { l1triggerType_.push_back(trigType); }
		void setPath(FourVectorHLTOffline::PathInfoCollection::iterator v) { v_ = v; }
		void setReco(edm::Handle<T> offColl) { offColl_ = offColl; }
		void setRecoB(edm::Handle<reco::JetTagCollection> offCollB) { offCollB_ = offCollB; }

    void fillOff();
		void monitorL1(const trigger::Vids & idtype, const trigger::Keys & l1k, const trigger::TriggerObjectCollection & toc);
    void monitorDenominator(FourVectorHLTOffline::PathInfoCollection::iterator v, bool l1accept, const trigger::Vids & idtype, const trigger::Keys & l1k, const trigger::TriggerObjectCollection& toc);

		void fillL1OffMatch(FourVectorHLTOffline* fv);
		void fillL1Match(FourVectorHLTOffline* fv)
		{
		  fillL1OffMatch(fv);
		}

		void monitorOnline(const trigger::Vids & idtype, const trigger::Keys & l1k, trigger::Keys::const_iterator ki, const trigger::TriggerObjectCollection & toc, unsigned int & NOn);
		void fillOnOffMatch(FourVectorHLTOffline* fv);
		void fillOnL1Match(FourVectorHLTOffline* fv, const trigger::Keys & l1k,  const trigger::TriggerObjectCollection & toc);
		void fillOnlineMatch(FourVectorHLTOffline* fv, const trigger::Keys & l1k,  const trigger::TriggerObjectCollection & toc)
		{

      if(! isTriggerType(v_->getObjectType()) ) return;
	    fillOnOffMatch(fv);
	    fillOnL1Match(fv, l1k, toc);

	  }

		void fillOffMatch(FourVectorHLTOffline* fv)
		{
      if(! isTriggerType(v_->getObjectType()) ) return;
		}
		void clearSets();

		bool isTriggerType(int t);
		bool isL1TriggerType(int t);

    mmset L1OffDRMatchSet;
    mmset L1MCDRMatchSet;
    mmset OnOffDRMatchSet;
    mmset OnMCDRMatchSet;
    mmset OnL1DRMatchSet;
    mmset OffMCDRMatchSet;


		void setBJetsFlag(bool flag) 
		{ 
		  BJetsFlag_ = flag; 
		}
		

private:

		int   pdgId_;
		int   pdgStatus_;

    float EtaMax_;
    float EtMin_;

		float DRMatch_;

		bool GenJetsFlag_;
		bool BJetsFlag_;

		std::vector<int> triggerType_;
		std::vector<int> l1triggerType_;

    edm::Handle<T> offColl_;
    edm::Handle<reco::JetTagCollection> offCollB_;

    FourVectorHLTOffline::PathInfoCollection::iterator v_;

};

template <class T> 
bool objMonData<T>::isTriggerType(int t)
{
  bool rc = false;

  for(std::vector<int>::const_iterator it = triggerType_.begin(); it != triggerType_.end(); ++it)
	{

	 if(t == *it) { rc = true; break; }

  } // end for

	return rc;

}


template <class T> 
bool objMonData<T>::isL1TriggerType(int t)
{
  bool rc = false;

  for(std::vector<int>::const_iterator it = l1triggerType_.begin(); it != l1triggerType_.end(); ++it)
	{

	 if(fabs(t) == fabs(*it)) { rc = true; break; }

  } // end for

	return rc;

}

template <class T> 
void objMonData<T>::monitorDenominator(FourVectorHLTOffline::PathInfoCollection::iterator v, bool l1accept, const trigger::Vids & idtype, const trigger::Keys & l1k, const trigger::TriggerObjectCollection& toc)
{

        setPath(v);
				
				if(! isTriggerType(v_->getObjectType()) ) return;

	      fillOff();

        if (l1accept) monitorL1(idtype, l1k, toc);


}

template <class T> 
void objMonData<T>::fillOff()
{

 unsigned int NOff = 0;

 if( offCollB_.isValid()) {
  typedef typename reco::JetTagCollection::const_iterator const_iterator;
  for( const_iterator iter = offCollB_->begin(), iend = offCollB_->end(); iter != iend; ++iter )
  {

	  float recoEta = (*iter).first->eta();
	  float recoPhi = (*iter).first->phi();
	  float recoPt = (*iter).first->pt();


    if (fabs(recoEta) <= EtaMax_ && recoPt >=  EtMin_ )
    {
	   
	     NOff++;
       v_->getOffEtOffHisto()->Fill(recoPt);
       v_->getOffEtaVsOffPhiOffHisto()->Fill(recoEta, recoPhi);

    }

  }

 }
 else if(offColl_.isValid()) {

  typedef typename T::const_iterator const_iterator;
  for( const_iterator iter = offColl_->begin(), iend = offColl_->end(); iter != iend; ++iter )
  {


   if (fabs(iter->eta()) <= EtaMax_ && iter->pt() >=  EtMin_ )
   {

	   NOff++;
     v_->getOffEtOffHisto()->Fill(iter->pt());
     v_->getOffEtaVsOffPhiOffHisto()->Fill(iter->eta(), iter->phi());

   }

  }

 } // end else if

 v_->getNOffHisto()->Fill(NOff);

}


template <class T> 
void objMonData<T>::monitorL1(const trigger::Vids & idtype, const trigger::Keys & l1k, const trigger::TriggerObjectCollection& toc)
{

 unsigned int NL1=0;
 unsigned int NL1OffUM=0;

 trigger::Vids::const_iterator idtypeiter = idtype.begin(); 
 for (trigger::Keys::const_iterator l1ki = l1k.begin(); l1ki !=l1k.end(); ++l1ki ) {

	 trigger::TriggerObject l1FV = toc[*l1ki];
	 if(isL1TriggerType(*idtypeiter))
	 {

			NL1++;


      if (fabs(l1FV.eta()) <= EtaMax_ && l1FV.pt() >= EtMin_)
      { 

        v_->getL1EtL1Histo()->Fill(l1FV.pt());
	      v_->getL1EtaVsL1PhiL1Histo()->Fill(l1FV.eta(), l1FV.phi());

	    }

      fimmap L1OffDRMatchMap;

	    if (offCollB_.isValid()) {

	      int j=0;
        typedef typename reco::JetTagCollection::const_iterator const_iterator;
        for( const_iterator iter = offCollB_->begin(), iend = offCollB_->end(); iter != iend; ++iter )
        {

				  float recoEta = (*iter).first->eta();
				  float recoPhi = (*iter).first->phi();
				  float recoPt = (*iter).first->pt();

          if (fabs(recoEta) <= EtaMax_ && recoPt >=  EtMin_ )
          {

				    // fill UM histos (no matching required)
				    if(NL1 == 1) {

							NL1OffUM++;
	            v_->getOffEtL1OffUMHisto()->Fill(recoPt);
	            v_->getOffEtaVsOffPhiL1OffUMHisto()->Fill(recoEta,recoPhi);

						}

						 // make maps of matched objects
	          float dR = reco::deltaR(recoEta,recoPhi,l1FV.eta(),l1FV.phi());
	          if ( dR < 1.0)
						{

		          L1OffDRMatchMap.insert(std::pair<float,int>(dR,j));

						}

          }

	        j++;

				}

		  }
	    else if (offColl_.isValid()) {

	      int j=0;
        typedef typename T::const_iterator const_iterator;
        for( const_iterator iter = offColl_->begin(), iend = offColl_->end(); iter != iend; ++iter )
        {

          if (fabs(iter->eta()) <= EtaMax_ && iter->pt() >=  EtMin_ )
          {

				    // fill UM histos (no matching required)
				    if(NL1 == 1) {

							NL1OffUM++;
	            v_->getOffEtL1OffUMHisto()->Fill(iter->pt());
	            v_->getOffEtaVsOffPhiL1OffUMHisto()->Fill(iter->eta(),iter->phi());

						}

						// make maps of matched objects
	          float dR = reco::deltaR(iter->eta(),iter->phi(),l1FV.eta(),l1FV.phi());
	          if ( dR < 1.0) 
						{

		         L1OffDRMatchMap.insert(std::pair<float,int>(dR,j));

						}

          }

	        j++;

        }

	     }
       if(! L1OffDRMatchMap.empty())  L1OffDRMatchSet.insert(L1OffDRMatchMap);


	   } // end if isL1TriggerType
     ++idtypeiter;

 } // end for l1ki

 v_->getNL1Histo()->Fill(NL1);
 v_->getNL1OffUMHisto()->Fill(NL1OffUM);

}

template <class T> 
void objMonData<T>::monitorOnline(const trigger::Vids & idtype, const trigger::Keys & l1k, trigger::Keys::const_iterator ki, const trigger::TriggerObjectCollection & toc, unsigned int & NOn)
{

		 unsigned int NOnOffUM=0;
		 unsigned int NOnL1UM=0;

		 if(! isTriggerType(v_->getObjectType()) ) return;

		 trigger::TriggerObject onlineFV = toc[*ki];

	   NOn++;    

     if (fabs(onlineFV.eta()) <= EtaMax_ && onlineFV.pt() >= EtMin_)
     { 

       v_->getOnEtOnHisto()->Fill(onlineFV.pt());
	     v_->getOnEtaVsOnPhiOnHisto()->Fill(onlineFV.eta(), onlineFV.phi());

	   }


     fimmap OnOffDRMatchMap;

	   if (offCollB_.isValid()) {

	      int j=0;
        typedef typename reco::JetTagCollection::const_iterator const_iterator;
        for( const_iterator iter = offCollB_->begin(), iend = offCollB_->end(); iter != iend; ++iter )
        {

				  float recoEta = (*iter).first->eta();
				  float recoPhi = (*iter).first->phi();
				  float recoPt = (*iter).first->pt();

          if (fabs(recoEta) <= EtaMax_ && recoPt >=  EtMin_ )
          {

				    // fill UM histos (no matching required)
				    if(NOn == 1) {

							NOnOffUM++;
	            v_->getOffEtOnOffUMHisto()->Fill(recoPt);
	            v_->getOffEtaVsOffPhiOnOffUMHisto()->Fill(recoEta,recoPhi);

						}

						 // make maps of matched objects
	          float dR = reco::deltaR(recoEta,recoPhi,onlineFV.eta(),onlineFV.phi());
	          if ( dR < 1.0)
						{

		          OnOffDRMatchMap.insert(std::pair<float,int>(dR,j));

						}

          }

	        j++;

				}

		  }
	    else if (offColl_.isValid()) {

	      int j=0;

        typedef typename T::const_iterator const_iterator;
        for( const_iterator iter = offColl_->begin(), iend = offColl_->end(); iter != iend; ++iter )
        {

          if (fabs(iter->eta()) <= EtaMax_ && iter->pt() >=  EtMin_ )
          {

				    // fill UM histos (no matching required)
				    if(NOn == 1) {

							NOnOffUM++;
	            v_->getOffEtOnOffUMHisto()->Fill(iter->pt());
	            v_->getOffEtaVsOffPhiOnOffUMHisto()->Fill(iter->eta(),iter->phi());

						}

						 // make maps of matched objects
	          float dR = reco::deltaR(iter->eta(),iter->phi(),onlineFV.eta(),onlineFV.phi());
	          if ( dR < 1.0)
						{

		          OnOffDRMatchMap.insert(std::pair<float,int>(dR,j));

						}

          }

	        j++;


        }

	     }

       if(! OnOffDRMatchMap.empty())  OnOffDRMatchSet.insert(OnOffDRMatchMap);



       fimmap OnL1DRMatchMap;
	     int j=0;
       trigger::Vids::const_iterator idtypeiter = idtype.begin(); 
       for (trigger::Keys::const_iterator l1ki = l1k.begin(); l1ki !=l1k.end(); ++l1ki ) 
			 {

			   

	       if(isL1TriggerType(*idtypeiter))
	       {

		       trigger::TriggerObject l1FV = toc[*l1ki];

	         if ( fabs(l1FV.eta()) <= EtaMax_ && l1FV.pt() >= EtMin_ )
           {

				      // fill UM histos (no matching required)
				      if(NOn == 1) {

							 NOnL1UM++;
	             v_->getL1EtL1OnUMHisto()->Fill(l1FV.pt());
	             v_->getL1EtaVsL1PhiL1OnUMHisto()->Fill(l1FV.eta(),l1FV.phi());

						   }


               float dR = reco::deltaR(l1FV.eta(),l1FV.phi(),onlineFV.eta(),onlineFV.phi());

	             if ( dR < 1.0) 
						   {

	               OnL1DRMatchMap.insert(std::pair<float,int>(dR,j));

						   }

						 } // end if l1FV eta, pt

          } // end if isL1TriggerType

	        ++idtypeiter;
	        j++;

	    } // end for

      if(! OnL1DRMatchMap.empty()) OnL1DRMatchSet.insert(OnL1DRMatchMap);


			v_->getNOnHisto()->Fill(NOn);
			v_->getNOnOffUMHisto()->Fill(NOnOffUM);
			v_->getNL1OnUMHisto()->Fill(NOnL1UM);

}

template <class T> 
void objMonData<T>::fillL1OffMatch(FourVectorHLTOffline* fv)
{

  float NL1Off=0;

  if(L1OffDRMatchSet.size() > 1) fv->cleanDRMatchSet(L1OffDRMatchSet);

	// clean the set L1-Off
	// now fill histos
  for ( mmset::iterator setIter = L1OffDRMatchSet.begin( ); setIter != L1OffDRMatchSet.end( ); setIter++ ) 
  {

       fimmap tempMap = *setIter;
         
       fimmap::iterator it = tempMap.begin(); 
       int i  = (*it).second ;
			 float dR = (*it).first;
	     v_->getOffDRL1OffHisto()->Fill(dR);

       if (dR > DRMatch_) continue;
       if( offCollB_.isValid()) {

         typedef typename JetTagCollection::const_iterator const_iterator;
			   const_iterator iter = offCollB_->begin();
         for (int count = 0; count < i; count++) iter++;


	       NL1Off++;
	       v_->getOffEtL1OffHisto()->Fill((*iter).first->pt());
	       v_->getOffEtaVsOffPhiL1OffHisto()->Fill((*iter).first->eta(),(*iter).first->phi());


			}
      else if( offColl_.isValid()) {

         typedef typename T::const_iterator const_iterator;
			   const_iterator iter = offColl_->begin();
         for (int count = 0; count < i; count++) iter++;


	       NL1Off++;
	       v_->getOffEtL1OffHisto()->Fill(iter->pt());
	       v_->getOffEtaVsOffPhiL1OffHisto()->Fill(iter->eta(),iter->phi());

			}

	}

	v_->getNL1OffHisto()->Fill(NL1Off);

}

template <class T> 
void objMonData<T>::fillOnOffMatch(FourVectorHLTOffline* fv)
{

  unsigned int NOnOff=0;

	// clean the set L1-Off
  if(OnOffDRMatchSet.size() > 1) fv->cleanDRMatchSet(OnOffDRMatchSet);
	// now fill histos
  for ( mmset::iterator setIter = OnOffDRMatchSet.begin( ); setIter != OnOffDRMatchSet.end( ); setIter++ ) 
  {


       fimmap tempMap = *setIter;
         
       fimmap::iterator it = tempMap.begin(); 
       int i  = (*it).second ;
			 float dR = (*it).first;
	     v_->getOffDROnOffHisto()->Fill(dR);
       

       if (dR > DRMatch_) continue;

       if( offCollB_.isValid()) {


         typedef typename reco::JetTagCollection::const_iterator const_iterator;
			   const_iterator iter = offCollB_->begin();
         for (int count = 0; count < i; count++) iter++;


	       NOnOff++;
	       v_->getOffEtOnOffHisto()->Fill((*iter).first->pt());
	       v_->getOffEtaVsOffPhiOnOffHisto()->Fill((*iter).first->eta(),(*iter).first->phi());

			 }
       else if( offColl_.isValid()) {

         typedef typename T::const_iterator const_iterator;
			   const_iterator iter = offColl_->begin();
         for (int count = 0; count < i; count++) iter++;

	       NOnOff++;
	       v_->getOffEtOnOffHisto()->Fill(iter->pt());
	       v_->getOffEtaVsOffPhiOnOffHisto()->Fill(iter->eta(),iter->phi());

			 }

	}

	v_->getNOnOffHisto()->Fill(NOnOff);

}


template <class T> 
void objMonData<T>::fillOnL1Match(FourVectorHLTOffline* fv, const trigger::Keys & l1k,  const trigger::TriggerObjectCollection & toc)
{

  unsigned int NOnL1=0;

	// clean the set On-L1
	if(OnL1DRMatchSet.size() > 1) fv->cleanDRMatchSet(OnL1DRMatchSet);
	// now fill histos
  for ( mmset::iterator setIter = OnL1DRMatchSet.begin( ); setIter != OnL1DRMatchSet.end( ); setIter++ ) 
  {

    fimmap tempMap = *setIter;
      
    fimmap::iterator it = tempMap.begin(); 
    int i  = (*it).second ;
		float dR = (*it).first;
	  v_->getL1DROnL1Histo()->Fill(dR);

    if (dR > DRMatch_) continue;

    trigger::Keys::const_iterator l1ki = l1k.begin();
    for (int count = 0; count < i; count++) l1ki++;

	  NOnL1++;
	  v_->getL1EtL1OnHisto()->Fill(toc[*l1ki].pt());
	  v_->getL1EtaVsL1PhiL1OnHisto()->Fill(toc[*l1ki].eta(),toc[*l1ki].phi());

	}

  v_->getNL1OnHisto()->Fill(NOnL1);

}


template <class T> 
void objMonData<T>::clearSets()
{

     L1OffDRMatchSet.clear();
     L1MCDRMatchSet.clear();
     OnOffDRMatchSet.clear();
     OnMCDRMatchSet.clear();
     OnL1DRMatchSet.clear();
     OffMCDRMatchSet.clear();

}


#endif
