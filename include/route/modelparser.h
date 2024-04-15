#ifndef INCLUDE_ROUTE_MODELPARSER_H_
#define INCLUDE_ROUTE_MODELPARSER_H_

#include<map>
#include<exception>

#include "common.h"
#include "fwd.h"
#include "util.h"

namespace piwcs::prw::router{

struct ParseResult{

	Graph graph;
	const GraphMetadata meta;

}; // struct ParseResult

class NotFoundException: public std::runtime_error{
public:
	NotFoundException(const std::string& _msg): std::runtime_error(_msg) {}
};

class SectionNotFoundException : public NotFoundException{
	SectionNotFoundException(const std::string& _msg): NotFoundException(_msg) {}
};

class NodeNotFoundException : public NotFoundException{
	NodeNotFoundException(const std::string& _msg): NotFoundException(_msg) {}
};


class ModelParser{
public:

	using ModelRef = const Model&;
	using ParseMap = IdMap<std::vector<Index>>;
	static constexpr Index INDEX_INVALID = ~0;

	struct RegNodeInfo{
		std::vector<Identifier> sections;
		std::vector<SlotId> slots;
	};

	/*
	 * Construct new ModelParser
	 */
	ModelParser(ModelRef _model);

	ModelParser() = delete;

	ParseResult parse() const;

INSPECTABLE:

	ModelRef m_model;
	ParseMap m_pmap;

	std::vector<RegNodeInfo> getNodeInfo(const Identifier& _id);

	const Node* resolveSection(const Identifier& _section_id, const Identifier& _from_id);


}; // class ModelParser

} // namespace piwcs::prw::router
#endif /* INCLUDE_ROUTE_MODELPARSER_H_ */
