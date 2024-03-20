#include "xsection.h"
#include <iostream>

#include "podio/Frame.h"

k4GeneratorsConfig::xsection::xsection():
  m_xsection(0.),
  m_xsectionError(0.),
  m_generator(""),
  m_process(""),
  m_file("")
{
  m_reader = new podio::ROOTReader();
}
k4GeneratorsConfig::xsection::xsection(double xsec, double xsecError, std::string generator, std::string process, std::string file)
{
  m_xsection      = xsec;
  m_xsectionError = xsecError;
  m_generator     = generator;
  m_process       = process;
  m_file          = file;

  m_reader = new podio::ROOTReader();
  processFile();
}
k4GeneratorsConfig::xsection::xsection(const xsection& theOriginal)
{
  if ( this != &theOriginal ){
    m_xsection      = theOriginal.m_xsection;
    m_xsectionError = theOriginal.m_xsectionError;
    m_generator     = theOriginal.m_generator;
    m_process       = theOriginal.m_process;
    m_file          = theOriginal.m_file;
    m_reader = new podio::ROOTReader();
  }
}
k4GeneratorsConfig::xsection& k4GeneratorsConfig::xsection::operator=(const xsection& theOriginal)
{
  if ( this != &theOriginal ){
    m_xsection      = theOriginal.m_xsection;
    m_xsectionError = theOriginal.m_xsectionError;
    m_generator     = theOriginal.m_generator;
    m_process       = theOriginal.m_process;
    m_file          = theOriginal.m_file;
    if (m_reader != 0 ) delete m_reader;
    m_reader = new podio::ROOTReader();
  }

  return *this;
}
k4GeneratorsConfig::xsection::~xsection(){
  delete m_reader;m_reader=0;
}
void k4GeneratorsConfig::xsection::processFile(){

  // open the edm4hep file
  m_reader->openFile(m_file);
  
  // retrieve the RunInfo for the weight names, there should only be 1 entry per Run
  m_reader->getEntries("RunInfo");
  auto runinfo = podio::Frame(m_reader->readNextEntry("RunInfo"));
  std::vector<std::string> weightNames = runinfo.getParameter<std::vector<std::string>>("WeightNames");
  if ( weightNames.size() > 0 ){
    std::cout << "k4GeneratorsConfig::Found Info on weight names: " << weightNames[0] << std::endl;
  }
  else {
    std::cout << "k4GeneratorsConfig::Error: Info on weight names not found" << std::endl;
  }

  std::cout << "Calculating last event" << std::endl;
  // retrieve the cross section for the last event
  if ( m_reader->getEntries("events") == 0 ){
    m_xsection      = 0.;
    m_xsectionError = 0.;
    return;
  }
  unsigned int lastEvent = m_reader->getEntries("events") - 1;
  std::cout << "last event " << lastEvent << " " << m_reader->getEntries("events") << std::endl;
  auto event = podio::Frame(m_reader->readEntry("events",lastEvent));
  
  // decode the cross sections
  std::cout << "get xsecrions" << std::endl;
  std::vector<double> xsections = event.getParameter<std::vector<double>>("CrossSections");
  std::cout << "fill m_xsection" << std::endl;
  m_xsection =  xsections.size()>0 ? xsections[0] : 0.;
  
  // decode the cross sections
  std::cout << "get xsecrionErrors" << std::endl;
  std::vector<double> xsectionErrors = event.getParameter<std::vector<double>>("CrossSectionErrors");
  std::cout << "fill xsection error" << std::endl;
  m_xsectionError =  xsectionErrors.size()>0 ? xsectionErrors[0] : 0.;
  std::cout << "Done with process event" << std::endl;

  return;
}
void k4GeneratorsConfig::xsection::setXsection(double xsec){
  m_xsection = xsec;
}
void k4GeneratorsConfig::xsection::setXsection(double xsec, double err){
  setXsection(xsec);
  setXsectionError(err);
}
void k4GeneratorsConfig::xsection::setXsectionError(double error){
  m_xsectionError = error;
}
void k4GeneratorsConfig::xsection::setGenerator(std::string gen){
  m_generator = gen;
}
void k4GeneratorsConfig::xsection::setProcess(std::string proc){
  m_process = proc;
}
void k4GeneratorsConfig::xsection::setFile(std::string file){
  m_file = file;
  processFile();
}
double k4GeneratorsConfig::xsection::Xsection(){
  return m_xsection;
}
double k4GeneratorsConfig::xsection::XsectionError(){
  return m_xsectionError;
}
std::string k4GeneratorsConfig::xsection::Generator(){
  return m_generator;
}
std::string k4GeneratorsConfig::xsection::Process(){
  return m_process;
}
std::string k4GeneratorsConfig::xsection::File(){
  return m_file;
}
void k4GeneratorsConfig::xsection::Print(){
  std::cout << std::endl;
  std::cout << "xsection object summary:" << std::endl;
  std::cout << "xsection      : " << m_xsection      
	    << " +- "             << m_xsectionError << " pb"<< std::endl;
  std::cout << "Generator     : " << m_generator     << std::endl;
  std::cout << "Process       : " << m_process       << std::endl;
  std::cout << "File          : " << m_file          << std::endl;
  std::cout << std::endl;
}
