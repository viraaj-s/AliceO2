# Copyright CERN and copyright holders of ALICE O2. This software is distributed
# under the terms of the GNU General Public License v3 (GPL Version 3), copied
# verbatim in the file "COPYING".
#
# See http://alice-o2.web.cern.ch/license for full licensing information.
#
# In applying this license CERN does not waive the privileges and immunities
# granted to it by virtue of its status as an Intergovernmental Organization or
# submit itself to any jurisdiction.

o2_add_executable(trackselection
                  SOURCES trackselection.cxx
                  PUBLIC_LINK_LIBRARIES O2::Framework O2::AnalysisDataModel O2::AnalysisCore
                  COMPONENT_NAME Analysis)

o2_add_executable(correlations
                  SOURCES correlations.cxx
                  PUBLIC_LINK_LIBRARIES O2::Framework O2::AnalysisCore
                  COMPONENT_NAME Analysis)

o2_add_executable(correlations-collection
                  SOURCES correlationsCollection.cxx
                  PUBLIC_LINK_LIBRARIES O2::Framework O2::AnalysisCore
                  COMPONENT_NAME Analysis)

o2_add_executable(vertexing-hf
	  	  SOURCES vertexerhf.cxx
		  PUBLIC_LINK_LIBRARIES O2::Framework O2::AnalysisDataModel O2::DetectorsVertexing
	          COMPONENT_NAME Analysis)

o2_add_executable(validation
	  	  SOURCES validation.cxx
		  PUBLIC_LINK_LIBRARIES O2::Framework O2::DetectorsBase
	          COMPONENT_NAME Analysis)

if(FastJet_FOUND)
o2_add_executable(jetfinder
  SOURCES jetfinder.cxx
  PUBLIC_LINK_LIBRARIES O2::Framework O2::AnalysisCore O2::AnalysisDataModel
                        FastJet::FastJet
  COMPONENT_NAME Analysis)
endif()

o2_add_executable(upc-an
                  SOURCES upcAnalysis.cxx
                  PUBLIC_LINK_LIBRARIES O2::Framework O2::AnalysisDataModel O2::DetectorsBase
                  COMPONENT_NAME Analysis)

o2_add_executable(event-selection
                  SOURCES eventSelection.cxx
                  PUBLIC_LINK_LIBRARIES O2::Framework O2::AnalysisDataModel O2::DetectorsBase
                  COMPONENT_NAME Analysis)

o2_add_executable(multiplicity-table
                  SOURCES multiplicityTable.cxx
                  PUBLIC_LINK_LIBRARIES O2::Framework O2::AnalysisDataModel O2::DetectorsBase
                  COMPONENT_NAME Analysis)

o2_add_executable(multiplicity-qa
                  SOURCES multiplicityQa.cxx
                  PUBLIC_LINK_LIBRARIES O2::Framework O2::AnalysisDataModel O2::DetectorsBase
                  COMPONENT_NAME Analysis)
                  
o2_add_executable(centrality-table
                  SOURCES centralityTable.cxx
                  PUBLIC_LINK_LIBRARIES O2::Framework O2::AnalysisDataModel O2::DetectorsBase
                  COMPONENT_NAME Analysis)

o2_add_executable(centrality-qa
                  SOURCES centralityQa.cxx
                  PUBLIC_LINK_LIBRARIES O2::Framework O2::AnalysisDataModel O2::DetectorsBase
                  COMPONENT_NAME Analysis)

