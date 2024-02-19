//
// Copyright 2017-2023 Valve Corporation.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#pragma once

#include "job_graph.h"

namespace ipl {

// --------------------------------------------------------------------------------------------------------------------
// ThreadPool
// --------------------------------------------------------------------------------------------------------------------

class ThreadPool
{
public:
    ThreadPool(int numThreads);

    ~ThreadPool();

    void process(JobGraph& jobGraph);

    void cancel();

private:
    Array<std::thread> mThreads;
    std::atomic<bool> mCancel;
    std::atomic<int> mReady;
    std::atomic<int> mCompleted;
    std::atomic<bool> mQuit;
    std::mutex mMutex;
    std::condition_variable mCondVarReady;
    std::condition_variable mCondVarComplete;
    JobGraph* mJobGraph;

    void threadFunc(int threadId);
};

}
