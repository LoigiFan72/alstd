//! @file alstdTest.h
//!
//! @author Stephen A

namespace alstd
{
class IAllocator;

class ITestSuite
{
public:
    ITestSuite(){ }

    virtual ~ITestSuite(){}
    virtual void initialize() = 0;
    virtual void finalize() = 0;
    virtual void startTest() = 0;
    virtual void prepareTest() = 0;
    virtual void endTest() = 0;
    virtual void setupTestEnv() = 0;
    
    virtual IAllocator* getTestAllocator() = 0;

    virtual bool isTestRunning(){ return mIsTestRunning; }

    bool mIsTestRunning;
};
}