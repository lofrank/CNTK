//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//

#pragma once

#include "DataDeserializer.h"
#include "HTKDataDeserializer.h"
#include "biggrowablevectors.h"
#include "CorpusDescriptor.h"

namespace Microsoft { namespace MSR { namespace CNTK {

struct MLFUtterance : public SequenceDescription
{
    // Where the sequence is stored in m_classIds
    size_t sequenceStart;
};

struct MLFFrame : public SequenceDescription
{
    // Where the sequence is stored in m_classIds
    size_t index;
};

class MLFDataDeserializer : public IDataDeserializer
{
    size_t m_dimension;
    TensorShapePtr m_layout;
    std::wstring m_stateListPath;
    std::vector<std::wstring> m_mlfPaths;

    // [classidsbegin+t] concatenation of all state sequences
    msra::dbn::biggrowablevector<msra::dbn::CLASSIDTYPE> m_classIds;

    std::vector<MLFUtterance> m_utterances;
    std::vector<MLFFrame> m_frames;

    SequenceDescriptions m_sequences;
    size_t m_elementSize;
    bool m_frameMode;
    std::wstring m_name;

    class MLFChunk;

public:
    MLFDataDeserializer(CorpusDescriptorPtr corpus, const ConfigParameters& label, size_t elementSize, bool framMode, const std::wstring& featureName);

    virtual const SequenceDescriptions& GetSequenceDescriptions() const override;

    virtual std::vector<StreamDescriptionPtr> GetStreamDescriptions() const override;

    virtual ChunkPtr GetChunk(size_t) override;

private:
    std::vector<SequenceDataPtr> GetSequenceById(size_t sequenceId);
};

typedef std::shared_ptr<MLFDataDeserializer> MLFDataDeserializerPtr;
} } }