/*  =========================================================================
    fty_srr_dto - Fty srr dto

    Copyright (C) 2014 - 2018 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
 */

#ifndef FTY_SRR_DTO_H_INCLUDED
#define FTY_SRR_DTO_H_INCLUDED

#include "fty_userdata_dto.h"

#include <memory>
#include <map>
#include <set>
#include <iostream>

#include "../include/srr_pb.h"

#include <cxxtools/serializationinfo.h>

namespace dto 
{
    namespace srr 
    {
        /**
         *  Status for SRR response object
         */
        /*std::string statusToString(Status status);
        Status stringToStatus(const std::string & statusStr);*/

        /**
         * Feature structures
         * 
         */
        using FeatureName = std::string;
        
        /**
         * Query wrapper functions
         * 
         */

        Query createSaveQuery(const std::set<FeatureName> & features, const std::string & passpharse);
        Query createRestoreQuery(const std::map<FeatureName, Feature> & restoreData, const std::string & passpharse);
        Query createResetQuery(const std::set<FeatureName> & features);
        Query createListFeatureQuery();

        //userdata serializer / deserializer
        void operator>> (UserData & data, Query & query);
        void operator<< (UserData & data, const Query & query);

        //ostream serializer => for tests mostly
        std::ostream& operator<< (std::ostream& os, const Query& q);

        //deserializer from UI => will be moved in fty-srr-rest
        Query saveQueryFromUiJson(const std::string & json);
        Query restoreQueryFromUiJson(const std::string & json);
        Query resetQueryFromUiJson(const std::string & json);

        void operator>>= (const cxxtools::SerializationInfo& si, SaveQuery & query);
        void operator>>= (const cxxtools::SerializationInfo& si, RestoreQuery & query);
        void operator>>= (const cxxtools::SerializationInfo& si, ResetQuery & query);
        
        //Comparison operators => for tests mostly
        inline bool operator==(const Feature& lhs, const Feature& rhs){ return ((lhs.data() == rhs.data()) &&(lhs.version() == rhs.version())); }
        inline bool operator!=(const Feature& lhs, const Feature& rhs){ return !(lhs == rhs); }
        
        inline bool operator==(const FeatureStatus& lhs, const FeatureStatus& rhs){ return ((lhs.status() == rhs.status()) && (lhs.error() == rhs.error())); }
        inline bool operator!=(const FeatureStatus& lhs, const FeatureStatus& rhs){ return !(lhs == rhs); }
        
        bool operator==(const Query& lhs, const Query& rhs);
        inline bool operator!=(const Query& lhs, const Query& rhs){ return !(lhs == rhs); }

        bool operator==(const SaveQuery& lhs, const SaveQuery& rhs);
        inline bool operator!=(const SaveQuery& lhs, const SaveQuery& rhs){ return !(lhs == rhs); }
        
        bool operator==(const RestoreQuery& lhs, const RestoreQuery& rhs);
        inline bool operator!=(const RestoreQuery& lhs, const RestoreQuery& rhs){ return !(lhs == rhs); }
        
        bool operator==(const ResetQuery& lhs, const ResetQuery& rhs);
        inline bool operator!=(const ResetQuery& lhs, const ResetQuery& rhs){ return !(lhs == rhs); }
        
        inline bool operator==(const ListFeatureQuery& lhs, const ListFeatureQuery& rhs){ return true; }
        inline bool operator!=(const ListFeatureQuery& lhs, const ListFeatureQuery& rhs){ return !(lhs == rhs); }

        /**
         * Response wrapper functions
         * 
         */

        //create functions
        Response createSaveResponse(const std::map<FeatureName, FeatureAndStatus> & mapFeaturesData);
        Response createRestoreResponse(const std::map<FeatureName, FeatureStatus> & mapStatus);
        Response createResetResponse(const std::map<FeatureName, FeatureStatus> & mapStatus);
        Response createGetListFeatureResponse(const std::map<FeatureName, FeatureDependencies> & mapFeaturesDependencies);

        //userdata serializer / deserializer
        void operator>> (UserData & data, Response & response);
        void operator<< (UserData & data, const Response & response);

        //ostream serializer => for tests mostly
        std::ostream& operator<< (std::ostream& os, const Response& r);

        //Comparison operators => for tests mostly      
        inline bool operator==(const FeatureAndStatus& lhs, const FeatureAndStatus& rhs){ return ((lhs.status() == rhs.status()) && (lhs.feature() == rhs.feature())); }
        inline bool operator!=(const FeatureAndStatus& lhs, const FeatureAndStatus& rhs){ return !(lhs == rhs); }

        bool operator==(const FeatureDependencies& lhs, const FeatureDependencies& rhs);
        inline bool operator!=(const FeatureDependencies& lhs, const FeatureDependencies& rhs){ return !(lhs == rhs); }
        
        bool operator==(const Response& lhs, const Response& rhs);
        inline bool operator!=(const Response& lhs, const Response& rhs){ return !(lhs == rhs); }

        bool operator==(const SaveResponse& lhs, const SaveResponse& rhs);
        inline bool operator!=(const SaveResponse& lhs, const SaveResponse& rhs){ return !(lhs == rhs); }
        
        bool operator==(const RestoreResponse& lhs, const RestoreResponse& rhs);
        inline bool operator!=(const RestoreResponse& lhs, const RestoreResponse& rhs){ return !(lhs == rhs); }
        
        bool operator==(const ResetResponse& lhs, const ResetResponse& rhs);
        inline bool operator!=(const ResetResponse& lhs, const ResetResponse& rhs){ return !(lhs == rhs); }
        
        bool operator==(const ListFeatureResponse& lhs, const ListFeatureResponse& rhs);
        inline bool operator!=(const ListFeatureResponse& lhs, const ListFeatureResponse& rhs){ return !(lhs == rhs); }

        //operators +        
        /*Response operator+(const Response & r1, const Response & r2);
        Response& operator+=(Response & r1, const Response & r2);

        SaveResponse& operator+=(SaveResponse & r1, const SaveResponse & r2);
        RestoreResponse& operator+=(RestoreResponse & r1, const RestoreResponse & r2);
        ResetResponse& operator+=(ResetResponse & r1, const ResetResponse & r2);
        ListFeatureResponse& operator+=(ListFeatureResponse & r1, const ListFeatureResponse & r2);*/

        //serializer for UI => will be moved in fty-srr-rest
        /*void operator<<= (const cxxtools::SerializationInfo& si, Response & response);
        void operator<<= (const cxxtools::SerializationInfo& si, SaveResponse & response);
        void operator<<= (const cxxtools::SerializationInfo& si, RestoreResponse & response);
        void operator<<= (const cxxtools::SerializationInfo& si, ResetResponse & response);
        void operator<<= (const cxxtools::SerializationInfo& si, ListFeatureResponse & response);

        //get global status for UI => will be moved in fty-srr-rest
        Status getGlobalStatus(const Response & r);

        Status getGlobalStatus(const SaveResponse & r);
        Status getGlobalStatus(const RestoreResponse & r);
        Status getGlobalStatus(const ResetResponse & r);
        Status getGlobalStatus(const ListFeatureResponse & r);*/
        

    } // srr namespace
    
} // dto namespace

#ifdef FTY_COMMON_DTO_BUILD_DRAFT_API
    // Tests
    void fty_srr_dto_test (bool verbose);

#endif // FTY_COMMON_DTO_BUILD_DRAFT_API

#endif
