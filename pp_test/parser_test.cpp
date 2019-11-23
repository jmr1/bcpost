//#include "stdafx.h"

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int argc, char** argv)
{
    // Define the file that will store the XML output.
    std::ofstream outputFile("unit.xml");

    /// Get the top level suite from the registry
    CppUnit::Test* suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    /// Adds the test to the list of test to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);

    // Change the default outputter to a compiler error format outputter
    // uncomment the following line if you need a compiler outputter.
    runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cout));

    // Change the default outputter to a xml error format outputter
    // uncomment the following line if you need a xml outputter.
    // runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(), outputFile));

    CPPUNIT_NS::BriefTestProgressListener* pBriefListener = new CPPUNIT_NS::BriefTestProgressListener;
    runner.eventManager().addListener(pBriefListener);

    std::string test;
    if (argc >= 2)
        test = argv[1];
    /// Run the tests.
    bool wasSuccessful = false;

    try
    {
        wasSuccessful = runner.run(test);
        // If you want to avoid the CppUnit typical output change the line above
        // by the following one:
        //  bool wasSucessful = runner.run("",false,false,false);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    outputFile.close();

    if (pBriefListener)
        delete pBriefListener;
    pBriefListener = NULL;

    std::cout << "Unit test was " << (wasSuccessful ? "successful.\n" : "NOT successful!\n") << std::endl;
    return wasSuccessful ? 0 : 1;
}
