#include <format>

#include "debug.h"
#include "route/modelparser.h"

namespace piwcs::prw::router {

ModelParser::ModelParser(ModelRef _model)
    : m_model(_model), m_pmap(ParseMap()) {}

ParseResult ModelParser::parse() const {
    // TODO: Preallocation
    ParseResult result;
    std::vector<std::vector<Identifier>> section_table;
    ParseMap pmap;
    for (auto &[id, node] : m_model.nodes()) {
        bool ins_result = pmap.insert(
            {id, std::vector<Index>(node.sectionCount(), INDEX_INVALID)});
        _ASSERT(
                ins_result,
                std::format("ParseMap insert failed with key: \"%s\"", id));

        /*
         * Get information on regular nodes from this model node
         */
        std::vector<RegularNodeInfo> rnodes = getNodeInfo(id);

        for (Index i=0; i<rnodes.size(); i++){
            /*
             * Set slots leading to this regular node
             */
            for (auto slot: rnodes[i].slots){
                // This node's index is that of after-the-last element of graph
                pmap[id][slot] = result.graph.size();
            }

            /*
             * Add this regular node to graph
             */
            result.graph.push_back(RouteNode(rnodes[i].sections.size()));

            /*
             * Pass section info to linking loop via section_table
             */
            section_table.push_back(std::move(rnodes[i].sections));
        }
    }
}

const Node *ModelParser::resolveSection(IdRef _section_id, IdRef _from_id) {
    const Node *start = m_model.node(_from_id);
    const Section *section = m_model.section(_section_id);

    _DEBUG_ONLY() if (!start) {
        _FAIL(std::format("Node with identifier \"%s\" not found", _from_id));
    }

    _DEBUG_ONLY() if (!section) {
        _FAIL(std::format("Section with identifier \"%s\" not found",
                          _section_id));
    }

    if (section->node(0) == _from_id) {
        // from is at slot 0 for this section
        return m_model.node(section->node(1));
    }

    if (section->node(1) == _from_id) {
        // from is at slot 1 for this section
        return m_model.node(section->node(0));
    }

    _FAIL(std::format("Section \"%s\" not connected to node \"%s\"",
                      _section_id, _from_id));
}

std::vector<ModelParser::RegularNodeInfo> ModelParser::getNodeInfo(IdRef _id) {
    const Node *node = m_model.node(_id);
    _ASSERT(node, std::format("Invalid node id encountered: \"%s\"", _id));

    NodeType type = node->type();
    std::vector<RegularNodeInfo> result;
    result.reserve(2);
    auto sections = std::vector<const Section *>(node->sectionCount(), nullptr);

    /* Check section list for nullptrs
     * (this should succeed on a correct model)
     */
    for (SlotId slot = 0; slot < node->sectionCount(); slot++) {
        sections[slot] = m_model.section(node->section(slot));
        _ASSERT(sections[slot],
                std::format("Invalid section id encountered: \"%s\" in node "
                            "\"%s\" section \"%s\"",
                            node->section(slot)));
    }

    /*
     * Construct regular nodes
     *
     * This is a trivial implementation which assigns every slot that can be
     * entered (labeled `start`) to a separate regular node. Constructed
     * regular node can be exited through sections in slots reachable from
     * `start` one.
     */
    for (SlotId start = 0; start < node->sectionCount(); start++) {

        bool isBidirectional = sections.at(start)->isBidir();
        bool isUnidirectional = sections.at(start)->isUnidir();
        bool isSectionEnd = sections.at(start)->end() == _id;

        // If slot cannot be entered it doesn't generate a regular node
        if (isBidirectional || (isUnidirectional && isSectionEnd)) {
            RegularNodeInfo thisResult;
            /*
             * Fill in inward slots leading to regular node
             *
             * In this case of trivial regular node construction every
             * regular node corresponds to a single `start` slot
             */
            thisResult.slots.push_back(start);

            /*
             * Fill in sections leading from this regular node
             *
             * Take every section that can be reached from `start`
             */
            for (SlotId end = 0; end < node->sectionCount(); end++) {
                if (node->couldTraverse(start, end)) {
                    thisResult.sections.push_back(sections.at(end)->id());
                }
            }

            // Fill in regular node metadata
            for (auto routedType : {MOTORIZED}) {
                if (type == routedType) {
                    thisResult.meta.requires_routing = true;
                    break;
                }
            }

            thisResult.meta.id_model = node->id();

            // Push current regular node to result
            result.push_back(std::move(thisResult));
        }
    }

    return std::move(result);
}

} // namespace piwcs::prw::router
