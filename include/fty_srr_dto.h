/*  =========================================================================
    fty_srr_dto - Fty srr dto

    Copyright (C) 2014 - 2020 Eaton

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

#include <cxxtools/serializationinfo.h>
#include "fty_userdata_dto.h"

#include "srr.pb.h"

#include "pb_helper.h"

#include <functional>
#include <string>
namespace dto 
{
    namespace srr 
    {
        constexpr auto PASS_PHRASE              = "passphrase";
        constexpr auto PASS_PHRASE_DEFINITION   = "passphraseDefinition";
        constexpr auto PASS_PHRASE_DESCRIPTION  = "passphraseDescription";
        constexpr auto FEATURE_LIST             = "featuresList";
        constexpr auto GROUP_LIST               = "group_list";
        constexpr auto DEPENDENCIES             = "dependencies";
        constexpr auto FEATURE_NAME             = "name";
        constexpr auto FEATURE_DESCRIPTION      = "description";
        constexpr auto DATA                     = "data";
        constexpr auto SRR_VERSION              = "version";
        constexpr auto CHECKSUM                 = "checksum";
        constexpr auto STATUS_LIST              = "statusList";
        constexpr auto STATUS                   = "status";
        constexpr auto ERROR                    = "error";
        // Type         
        constexpr auto SAVE_TYPE                = "save";
        constexpr auto RESTORE_TYPE             = "restore";
        constexpr auto RESET_TYPE               = "reset";
        constexpr auto LIST_TYPE                = "list";
        
        /**
         * Utils
         */
        cxxtools::SerializationInfo deserializeJson(const std::string & json);
        std::string serializeJson(const cxxtools::SerializationInfo & si, bool beautify = false);

        /**
         * Helper for client of SRR.
         * As a client of SRR, you have to implement the handlers functions 
         * 
         */
        class SrrQueryProcessor
        {
        public:
            std::function<SaveResponse(const SaveQuery &)> saveHandler;
            std::function<RestoreResponse(const RestoreQuery &)> restoreHandler;
            std::function<ResetResponse(const ResetQuery &)> resetHandler;
            std::function<ListFeatureResponse(const ListFeatureQuery &)> listFeatureHandler;

            Response processQuery(const Query & q);
        };
        
        /**
         * Query wrapper functions
         * 
         */

        using FeatureName = std::string;

        Query createSaveQuery(const std::set<FeatureName> & features, const std::string & passpharse);
        Query createRestoreQuery(const std::map<FeatureName, Feature> & restoreData, const std::string & passpharse, const std::string & version, const std::string & checksum);
        Query createRestoreListQuery(const std::list<std::map<FeatureName, Feature>>& restoreData, const std::string & passpharse, const std::string & version);
        Query createResetQuery(const std::set<FeatureName> & features, const std::string & version);
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
        
        void operator<<= (cxxtools::SerializationInfo& si, const SaveQuery & query);
        void operator<<= (cxxtools::SerializationInfo& si, const RestoreQuery & query);
        void operator<<= (cxxtools::SerializationInfo& si, const ResetQuery & query);

        void operator>>= (const cxxtools::SerializationInfo& si, Feature & feature);
        void operator<<= (cxxtools::SerializationInfo& si, const Feature & feature);
        
        //Comparison operators => for tests mostly
        inline bool operator==(const Feature& lhs, const Feature& rhs){ return ((lhs.data() == rhs.data()) &&(lhs.version() == rhs.version())); }
        inline bool operator!=(const Feature& lhs, const Feature& rhs){ return !(lhs == rhs); }
        
        inline bool operator<(const Feature& lhs, const Feature& rhs){ return (lhs.data() < rhs.data()); }
        
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
        Response createSaveResponse(const std::map<FeatureName, FeatureAndStatus> & mapFeaturesData, const std::string & version);
        Response createSaveResponse(const std::string & version, const FeatureStatus & featureStatus);
        Response createSaveResponse(const std::map<FeatureName, FeatureAndStatus> & mapFeaturesData, const std::string & version, const std::string & checksum, const FeatureStatus & featureStatus);
        Response createRestoreResponse(const std::map<FeatureName, FeatureStatus> & mapStatus);
        Response createRestoreResponse(const FeatureStatus & featureStatus, const std::map<FeatureName, FeatureStatus> & mapStatus);
        Response createRestoreResponse(const FeatureStatus & featureStatus);
        Response createResetResponse(const std::map<FeatureName, FeatureStatus> & mapStatus);
        Response createListFeatureResponse(const std::map<FeatureName, FeatureDependencies> & mapFeaturesDependencies, const std::string & version, const std::string & passphrassDefinition);
        Response createListFeatureResponse(const std::map<FeatureName, FeatureDependencies> & mapFeaturesDependencies, const std::string & version, const std::string & passphrassDefinition, const std::string & passphrassDescription);

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
        Response operator+(const Response & r1, const Response & r2);
        Response& operator+=(Response & r1, const Response & r2);

        SaveResponse& operator+=(SaveResponse & r1, const SaveResponse & r2);
        RestoreResponse& operator+=(RestoreResponse & r1, const RestoreResponse & r2);
        ResetResponse& operator+=(ResetResponse & r1, const ResetResponse & r2);
        ListFeatureResponse& operator+=(ListFeatureResponse & r1, const ListFeatureResponse & r2);

        //serializer for UI => will be moved in fty-srr-rest
        std::string responseToUiJson(const Response & response, bool beautiful = false);
        void operator<<= (cxxtools::SerializationInfo& si, const Response & response);
        void operator<<= (cxxtools::SerializationInfo& si, const SaveResponse & response);
        void operator<<= (cxxtools::SerializationInfo& si, const RestoreResponse & response);
        void operator<<= (cxxtools::SerializationInfo& si, const ResetResponse & response);
        void operator<<= (cxxtools::SerializationInfo& si, const ListFeatureResponse & response);

        void operator>>= (const cxxtools::SerializationInfo& si, SaveResponse & response);
        void operator>>= (const cxxtools::SerializationInfo& si, RestoreResponse & response);
        void operator>>= (const cxxtools::SerializationInfo& si, ResetResponse & response);
        void operator>>= (const cxxtools::SerializationInfo& si, ListFeatureResponse & response);

        //status to string for UI
        std::string statusToString(Status status);
        Status stringToStatus(const std::string& statusStr);

        //get global status for UI => will be moved in fty-srr-rest
        Status getGlobalStatus(const SaveResponse & r);
        Status getGlobalStatus(const RestoreResponse & r);
        Status getGlobalStatus(const ResetResponse & r);
        Status getGlobalStatus(const ListFeatureResponse & r);

    } // srr namespace
    
} // dto namespace


// Tests
    void fty_srr_dto_test (bool verbose);



#endif
