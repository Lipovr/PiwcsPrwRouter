#include <format>

#include "debug.h"
#include"route/modelparser.h"


namespace piwcs::prw::router{

	ModelParser::ModelParser(ModelRef _model):
			  m_model(_model)
			, m_pmap(ParseMap())
	{}

	ParseResult ModelParser::parse() const{
		ParseMap pmap;
		for (auto& [id, node]: m_model.nodes()) {
			bool ins_result = pmap.insert({id, std::vector<Index>(node.sectionCount(), INDEX_INVALID)});

		}
	}

	const Node* ModelParser::resolveSection(const Identifier& _section_id, const Identifier& _from_id){
		const Node* start = m_model.node(_from_id);
		const Section* section = m_model.section(_section_id);

		_DEBUG_ONLY() if (!start){
			_FAIL(std::format("Node with identifier \"%s\" not found", _from_id));
		}

		_DEBUG_ONLY() if (!section){
			_FAIL(std::format("Section with identifier \"%s\" not found", _section_id));
		}

		if (section->node(0)==_from_id){
			// from is at slot 0 for this section
			return m_model.node(section->node(1));
		}

		if (section->node(1)==_from_id){
			// from is at slot 1 for this section
			return m_model.node(section->node(0));
		}

		_FAIL(std::format("Section \"%s\" not connected to node \"%s\"", _section_id, _from_id));
	}

} // namespace piwcs::prw::router
