/*
 memory.h     MindForger thinking notebook

 Copyright (C) 2016-2018 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef M8R_MEMORY_H_
#define M8R_MEMORY_H_

#include <vector>
#include <map>

#include "../debug.h"
#include "../exceptions.h"
#include "../mind/ontology/ontology.h"
#include "../config/configuration.h"
#include "../repository_indexer.h"
#include "../representations/markdown/markdown.h"
#include "../representations/markdown/markdown_outline_representation.h"
#include "../model/outline.h"
#include "../model/note.h"
#include "../model/stencil.h"
#include "../model/tag.h"
#include "../model/resource_types.h"
#include "../persistence/persistence.h"
#include "../persistence/filesystem_persistence.h"

namespace m8r {

class Memory
{
private:
    /**
     * @brief Cache outlines in memory.
     *
     * If FALSE, then outlines are always loaded from
     * filesystem on get(), else keep already loaded outline
     * ASTs in memory.
     */
    bool cache;

    Configuration& config;
    RepositoryIndexer repositoryIndexer;
    Ontology ontology;
    MarkdownOutlineRepresentation representation;
    Persistence* persistence;

    std::vector<Outline*> outlines;
    std::vector<Note*> notes;
    std::vector<Stencil*> outlineStencils;
    std::vector<Stencil*> noteStencils;

    std::vector<Outline*> limboOutlines;

    // IMPROVE unordered_map
    std::map<std::string,Outline*> outlinesMap;

public:
    explicit Memory(Configuration& configuration);
    Memory(const Memory&) = delete;
    Memory(const Memory&&) = delete;
    Memory& operator=(const Memory&) = delete;
    Memory& operator=(const Memory&&) = delete;
    virtual ~Memory();

    std::vector<Stencil*>& getStencils(ResourceType type=ResourceType::OUTLINE);

    /**
     * @brief Learn repository content.
     */
    void learn();
    /**
     * @brief Create Outline from stencil, but don't learn it yet.
     */
    Outline* learnOutline(Stencil* stencil);
    Note* learnNote(Stencil* stencil);

    /**
     * @brief Remember known Outline by saving it.
     */
    void remember(const std::string& outlineKey);

    /**
     * @brief Remember new Outline.
     */
    void remember(Outline* outline);

    /**
     * @brief Forget Outline.
     */
    void forget(Outline* outline);

    /**
     * @brief Get Ontology.
     * @return Ontology
     */
    Ontology& getOntology(void) { return ontology; }

    /**
     * @brief Get the number of outlines.
     */
    int getOutlinesCount(void) const;

    /**
     * @brief Get the size of outline MDs in bytes.
     */
    unsigned int getOutlineMarkdownsSize(void) const;

    /**
     * @brief Get the number of notes of all outlines.
     */
    int getNotesCount(void) const;

    std::string createOutlineKey(const std::string* title);
    std::string createLimboKey(const std::string* title);

    /**
     * @brief Get list of outlines.
     *
     * Get list of outlines - title/description/metadata presence
     * is guaranteed, while AST is not.
     */
    const std::vector<Outline*>& getOutlines(void) const;

    /**
     * @brief Get full outline.
     *
     * Get outline including AST - if Outline contains only title/description/metadata,
     * then AST is loaded and full outline returned.
     */
    Outline* getOutline(const std::string &key);

    /**
     * @brief Full text search.
     *
     * Iterates outlines and calls fts() on each of them to get
     * matching outline's/note's description(s).
     */
    std::vector<std::string*>* ftsMatch(const std::string* exactMatchString) const;
    std::vector<std::string*>* fts(const std::string* regexp) const;

private:
    const OutlineType* toOutlineType(const MarkdownAstSectionMetadata&);

};

} /* namespace */

#endif /* M8R_MEMORY_H_ */