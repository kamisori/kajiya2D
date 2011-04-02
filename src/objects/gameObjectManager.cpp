/*
    kajiya2D is an editor for leveldata for heikiko2D/nodachi2D.
    Copyright (C) 2010-2011  Paul Predkiewicz

    kajiya2D is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <objects/spacialObject.hpp>
#include <objects/visualAppearance.hpp>
#include <objects/gameObjectManager.hpp>
namespace objects{

    char* GameObjectManager::fetchFileData( std::string* fileName, int fields )
    {
        std::ifstream ifs( fileName->c_str(), std::ifstream::in );
        char* buffer;
        if( ifs.is_open() ){
            int length;

            ifs.seekg( 0,std::ios::end );
            length = ifs.tellg();
            ifs.seekg( 0,std::ios::beg );

            buffer = new char[ length ];
            for(int i = 0; i < length; i++){
                buffer[i]=0;
            }

            ifs.read( buffer, length );
            ifs.close();
            return buffer;
        }
        exit(1);
    }

    void GameObjectManager::dumpFileData( std::string fileName, std::string outFileData )
    {
        while(outFileData.length() < 64 )
        {
            outFileData += "#";
        }
        std::ofstream ofs(fileName.c_str(), std::ofstream::trunc);
        ofs.write( outFileData.c_str() , outFileData.length() );
        ofs.close();
    }

    FileEntry* GameObjectManager::parseFileEntry( std::string* entry, std::string* dataDivider )
    {
        unsigned int lastData = 0;
        unsigned int nextData = entry->find( (*dataDivider), lastData );
        unsigned int dataLength = nextData - lastData;
        FileEntry* tmpEntry = new FileEntry();

        while( ( nextData != std::string::npos) && ( nextData < entry->length()) )
        {
            std::string tmpstr = entry->substr( lastData, dataLength );
            tmpEntry->push_back( tmpstr );

            lastData = nextData + dataDivider->length();
            nextData = entry->find( (*dataDivider), lastData );
            dataLength = nextData - lastData;
        }

        return tmpEntry;
    }

    FileData* GameObjectManager::parseFileData( std::string* fileName, int fields )
    {
        std::string fileContent;
        fileContent.clear();
        fileContent.assign( fetchFileData( fileName, fields ) );

        std::string entryDivider ("\r\n");
        std::string dataDivider (";");

        unsigned int lastEntry = 0;
        unsigned int nextEntry = fileContent.find( entryDivider, lastEntry );
        unsigned int entryLength = nextEntry - lastEntry;
        FileData* tmpData = new FileData();

        while( (nextEntry != std::string::npos) && ( nextEntry < fileContent.length() ) )
        {
            std::string temporaryEntryString = fileContent.substr( lastEntry, entryLength );
            FileEntry* tmpEntry = parseFileEntry( &temporaryEntryString, &dataDivider );
            tmpData->push_back( (*tmpEntry) );

            lastEntry = nextEntry+entryDivider.length();
            nextEntry = fileContent.find( entryDivider, lastEntry );
            entryLength = nextEntry - lastEntry;
        }
        return tmpData;
    }


    void GameObjectManager::loadMaterials( std::string materialFile )
    {
        FileData* dataFromFile = parseFileData( &materialFile, 24 );
        FileData::iterator itData;

        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileEntry tmp = (*itData);

            Material* temporaryMaterial = new Material(tmp);
            this->materialLibrary_.push_back( temporaryMaterial );

        }
    }

    void GameObjectManager::loadVisualAppearances( std::string visualAppearanceFile )
    {
        FileData* dataFromFile = parseFileData( &visualAppearanceFile, 2 );
        FileData::iterator itData;

        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileEntry tmp = (*itData);
            VisualAppearance* temporaryVisualAppearance = new VisualAppearance( tmp );
            this->visualAppearancesLibrary_.push_back( temporaryVisualAppearance );
        }
    }

    void GameObjectManager::loadObjects( std::string spacialObjectsFile )
    {
        FileData* dataFromFile = parseFileData( &spacialObjectsFile, 4 );
        FileData::iterator itData;

        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileEntry tmp = (*itData);
            SpacialObject* temporaryObject = new SpacialObject( tmp );
            if( temporaryObject != NULL )
            {
                this->spacialObjects_.push_back( temporaryObject );
            }
        }
    }

    void GameObjectManager::saveMaterials( std::string materialFile )
    {
        std::vector< Material* >::iterator it;
        std::string fileContent;
        fileContent = "";
        for( it = this->materialLibrary_.begin(); it < this->materialLibrary_.end(); it++ )
        {
            fileContent += (*it)->constructFileEntry();
            if( it+1 != this->materialLibrary_.end() )
             fileContent += "\r\n";
        }
        dumpFileData(materialFile, fileContent);
    }
    void GameObjectManager::saveVisualAppearances( std::string visualAppearanceFile )
    {
        std::vector< VisualAppearance* >::iterator it;
        std::string fileContent;
        fileContent = "";
        for( it = this->visualAppearancesLibrary_.begin(); it < this->visualAppearancesLibrary_.end(); it++ )
        {
            fileContent += (*it)->constructFileEntryAndSaveAnimations();
            if( it+1 != this->visualAppearancesLibrary_.end() )
             fileContent += "\r\n";
        }
        dumpFileData(visualAppearanceFile, fileContent);
    }
    void GameObjectManager::saveObjects( std::string spacialObjectsFile )
    {
        std::vector< SpacialObject* >::iterator it;
        std::string fileContent;
        fileContent = "";
        for( it = this->spacialObjects_.begin(); it < this->spacialObjects_.end(); it++ )
        {
            fileContent += (*it)->constructFileEntry();
            if( it+1 != this->spacialObjects_.end() )
             fileContent += "\r\n";
        }
        dumpFileData(spacialObjectsFile, fileContent);
    }

    VisualAppearance* GameObjectManager::provideVisualAppearance( std::string visualAppearanceId )
    {
        std::vector< VisualAppearance* >::iterator it;
        for( it = this->visualAppearancesLibrary_.begin(); it < this->visualAppearancesLibrary_.end(); it++ )
        {
            std::string foostr = (*it)->getVisualAppearanceId();
            if( visualAppearanceId.compare( (*it)->getVisualAppearanceId() ) == 0 )
            {
                return (*it);
            }
        }
        exit(1);
    }

    Material* GameObjectManager::provideMaterial( std::string materialId )
    {
        std::vector< Material* >::iterator it;
        for( it = this->materialLibrary_.begin(); it < this->materialLibrary_.end(); it++ )
        {
            if( materialId.compare( (*it)->getMaterialId() ) == 0 )
            {
                return (*it);
            }
        }
        exit(1);
    }

    SpacialObject* GameObjectManager::nextSpacialObject( int current )
    {
         std::vector< SpacialObject* >::iterator it;
         it = this->spacialObjects_.begin();
         it += current;
         if( it < this->spacialObjects_.end() )
         {
            return (*it);
         }
         return NULL;
    }

    VisualAppearance* GameObjectManager::nextVisualAppearance( int current )
    {
         std::vector< VisualAppearance* >::iterator it;
         it = this->visualAppearancesLibrary_.begin();
         it += current;
         if( it < this->visualAppearancesLibrary_.end() )
         {
            return (*it);
         }
         return NULL;
    }


    GameObjectManager::GameObjectManager()
    {
    }

    GameObjectManager::~GameObjectManager()
    {
        this->spacialObjects_.clear();
        this->visualAppearancesLibrary_.clear();
        this->materialLibrary_.clear();
    }
}
