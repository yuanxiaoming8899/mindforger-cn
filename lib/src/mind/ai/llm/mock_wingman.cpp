/*
 mock_wingman.cpp     MindForger thinking notebook

 Copyright (C) 2016-2024 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "mock_wingman.h"

namespace m8r {

using namespace std;

MockWingman::MockWingman()
    : Wingman(WingmanLlmProviders::WINGMAN_PROVIDER_MOCK)
{
}

MockWingman::~MockWingman()
{
}


void MockWingman::chat(const std::string& prompt, std::string& answer)
{
    MF_DEBUG("MockWingman::summarize() text:" << prompt << endl);

    answer.assign("chat(MOCK, '"+prompt+"')");

    MF_DEBUG("MockWingman::summarize() summary:" << answer << endl);
}

} // m8r namespace
