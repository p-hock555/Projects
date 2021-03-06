// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: leaderboard.proto

package cs201game.protos;

public final class LeaderboardProto {
  private LeaderboardProto() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }

  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
    registerAllExtensions(
        (com.google.protobuf.ExtensionRegistryLite) registry);
  }
  public interface LeaderboardOrBuilder extends
      // @@protoc_insertion_point(interface_extends:CS201Game.Leaderboard)
      com.google.protobuf.MessageOrBuilder {

    /**
     * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
     */
    java.util.List<cs201game.protos.PlayerScoreProto.PlayerScore> 
        getScoresList();
    /**
     * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
     */
    cs201game.protos.PlayerScoreProto.PlayerScore getScores(int index);
    /**
     * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
     */
    int getScoresCount();
    /**
     * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
     */
    java.util.List<? extends cs201game.protos.PlayerScoreProto.PlayerScoreOrBuilder> 
        getScoresOrBuilderList();
    /**
     * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
     */
    cs201game.protos.PlayerScoreProto.PlayerScoreOrBuilder getScoresOrBuilder(
        int index);
  }
  /**
   * Protobuf type {@code CS201Game.Leaderboard}
   */
  public static final class Leaderboard extends
      com.google.protobuf.GeneratedMessageV3 implements
      // @@protoc_insertion_point(message_implements:CS201Game.Leaderboard)
      LeaderboardOrBuilder {
  private static final long serialVersionUID = 0L;
    // Use Leaderboard.newBuilder() to construct.
    private Leaderboard(com.google.protobuf.GeneratedMessageV3.Builder<?> builder) {
      super(builder);
    }
    private Leaderboard() {
      scores_ = java.util.Collections.emptyList();
    }

    @java.lang.Override
    @SuppressWarnings({"unused"})
    protected java.lang.Object newInstance(
        UnusedPrivateParameter unused) {
      return new Leaderboard();
    }

    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
    getUnknownFields() {
      return this.unknownFields;
    }
    private Leaderboard(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      this();
      if (extensionRegistry == null) {
        throw new java.lang.NullPointerException();
      }
      int mutable_bitField0_ = 0;
      com.google.protobuf.UnknownFieldSet.Builder unknownFields =
          com.google.protobuf.UnknownFieldSet.newBuilder();
      try {
        boolean done = false;
        while (!done) {
          int tag = input.readTag();
          switch (tag) {
            case 0:
              done = true;
              break;
            case 10: {
              if (!((mutable_bitField0_ & 0x00000001) != 0)) {
                scores_ = new java.util.ArrayList<cs201game.protos.PlayerScoreProto.PlayerScore>();
                mutable_bitField0_ |= 0x00000001;
              }
              scores_.add(
                  input.readMessage(cs201game.protos.PlayerScoreProto.PlayerScore.parser(), extensionRegistry));
              break;
            }
            default: {
              if (!parseUnknownField(
                  input, unknownFields, extensionRegistry, tag)) {
                done = true;
              }
              break;
            }
          }
        }
      } catch (com.google.protobuf.InvalidProtocolBufferException e) {
        throw e.setUnfinishedMessage(this);
      } catch (java.io.IOException e) {
        throw new com.google.protobuf.InvalidProtocolBufferException(
            e).setUnfinishedMessage(this);
      } finally {
        if (((mutable_bitField0_ & 0x00000001) != 0)) {
          scores_ = java.util.Collections.unmodifiableList(scores_);
        }
        this.unknownFields = unknownFields.build();
        makeExtensionsImmutable();
      }
    }
    public static final com.google.protobuf.Descriptors.Descriptor
        getDescriptor() {
      return cs201game.protos.LeaderboardProto.internal_static_CS201Game_Leaderboard_descriptor;
    }

    @java.lang.Override
    protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return cs201game.protos.LeaderboardProto.internal_static_CS201Game_Leaderboard_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              cs201game.protos.LeaderboardProto.Leaderboard.class, cs201game.protos.LeaderboardProto.Leaderboard.Builder.class);
    }

    public static final int SCORES_FIELD_NUMBER = 1;
    private java.util.List<cs201game.protos.PlayerScoreProto.PlayerScore> scores_;
    /**
     * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
     */
    @java.lang.Override
    public java.util.List<cs201game.protos.PlayerScoreProto.PlayerScore> getScoresList() {
      return scores_;
    }
    /**
     * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
     */
    @java.lang.Override
    public java.util.List<? extends cs201game.protos.PlayerScoreProto.PlayerScoreOrBuilder> 
        getScoresOrBuilderList() {
      return scores_;
    }
    /**
     * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
     */
    @java.lang.Override
    public int getScoresCount() {
      return scores_.size();
    }
    /**
     * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
     */
    @java.lang.Override
    public cs201game.protos.PlayerScoreProto.PlayerScore getScores(int index) {
      return scores_.get(index);
    }
    /**
     * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
     */
    @java.lang.Override
    public cs201game.protos.PlayerScoreProto.PlayerScoreOrBuilder getScoresOrBuilder(
        int index) {
      return scores_.get(index);
    }

    private byte memoizedIsInitialized = -1;
    @java.lang.Override
    public final boolean isInitialized() {
      byte isInitialized = memoizedIsInitialized;
      if (isInitialized == 1) return true;
      if (isInitialized == 0) return false;

      memoizedIsInitialized = 1;
      return true;
    }

    @java.lang.Override
    public void writeTo(com.google.protobuf.CodedOutputStream output)
                        throws java.io.IOException {
      for (int i = 0; i < scores_.size(); i++) {
        output.writeMessage(1, scores_.get(i));
      }
      unknownFields.writeTo(output);
    }

    @java.lang.Override
    public int getSerializedSize() {
      int size = memoizedSize;
      if (size != -1) return size;

      size = 0;
      for (int i = 0; i < scores_.size(); i++) {
        size += com.google.protobuf.CodedOutputStream
          .computeMessageSize(1, scores_.get(i));
      }
      size += unknownFields.getSerializedSize();
      memoizedSize = size;
      return size;
    }

    @java.lang.Override
    public boolean equals(final java.lang.Object obj) {
      if (obj == this) {
       return true;
      }
      if (!(obj instanceof cs201game.protos.LeaderboardProto.Leaderboard)) {
        return super.equals(obj);
      }
      cs201game.protos.LeaderboardProto.Leaderboard other = (cs201game.protos.LeaderboardProto.Leaderboard) obj;

      if (!getScoresList()
          .equals(other.getScoresList())) return false;
      if (!unknownFields.equals(other.unknownFields)) return false;
      return true;
    }

    @java.lang.Override
    public int hashCode() {
      if (memoizedHashCode != 0) {
        return memoizedHashCode;
      }
      int hash = 41;
      hash = (19 * hash) + getDescriptor().hashCode();
      if (getScoresCount() > 0) {
        hash = (37 * hash) + SCORES_FIELD_NUMBER;
        hash = (53 * hash) + getScoresList().hashCode();
      }
      hash = (29 * hash) + unknownFields.hashCode();
      memoizedHashCode = hash;
      return hash;
    }

    public static cs201game.protos.LeaderboardProto.Leaderboard parseFrom(
        java.nio.ByteBuffer data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static cs201game.protos.LeaderboardProto.Leaderboard parseFrom(
        java.nio.ByteBuffer data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static cs201game.protos.LeaderboardProto.Leaderboard parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static cs201game.protos.LeaderboardProto.Leaderboard parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static cs201game.protos.LeaderboardProto.Leaderboard parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static cs201game.protos.LeaderboardProto.Leaderboard parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static cs201game.protos.LeaderboardProto.Leaderboard parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseWithIOException(PARSER, input);
    }
    public static cs201game.protos.LeaderboardProto.Leaderboard parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseWithIOException(PARSER, input, extensionRegistry);
    }
    public static cs201game.protos.LeaderboardProto.Leaderboard parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseDelimitedWithIOException(PARSER, input);
    }
    public static cs201game.protos.LeaderboardProto.Leaderboard parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseDelimitedWithIOException(PARSER, input, extensionRegistry);
    }
    public static cs201game.protos.LeaderboardProto.Leaderboard parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseWithIOException(PARSER, input);
    }
    public static cs201game.protos.LeaderboardProto.Leaderboard parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseWithIOException(PARSER, input, extensionRegistry);
    }

    @java.lang.Override
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder() {
      return DEFAULT_INSTANCE.toBuilder();
    }
    public static Builder newBuilder(cs201game.protos.LeaderboardProto.Leaderboard prototype) {
      return DEFAULT_INSTANCE.toBuilder().mergeFrom(prototype);
    }
    @java.lang.Override
    public Builder toBuilder() {
      return this == DEFAULT_INSTANCE
          ? new Builder() : new Builder().mergeFrom(this);
    }

    @java.lang.Override
    protected Builder newBuilderForType(
        com.google.protobuf.GeneratedMessageV3.BuilderParent parent) {
      Builder builder = new Builder(parent);
      return builder;
    }
    /**
     * Protobuf type {@code CS201Game.Leaderboard}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessageV3.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:CS201Game.Leaderboard)
        cs201game.protos.LeaderboardProto.LeaderboardOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return cs201game.protos.LeaderboardProto.internal_static_CS201Game_Leaderboard_descriptor;
      }

      @java.lang.Override
      protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return cs201game.protos.LeaderboardProto.internal_static_CS201Game_Leaderboard_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                cs201game.protos.LeaderboardProto.Leaderboard.class, cs201game.protos.LeaderboardProto.Leaderboard.Builder.class);
      }

      // Construct using cs201game.protos.LeaderboardProto.Leaderboard.newBuilder()
      private Builder() {
        maybeForceBuilderInitialization();
      }

      private Builder(
          com.google.protobuf.GeneratedMessageV3.BuilderParent parent) {
        super(parent);
        maybeForceBuilderInitialization();
      }
      private void maybeForceBuilderInitialization() {
        if (com.google.protobuf.GeneratedMessageV3
                .alwaysUseFieldBuilders) {
          getScoresFieldBuilder();
        }
      }
      @java.lang.Override
      public Builder clear() {
        super.clear();
        if (scoresBuilder_ == null) {
          scores_ = java.util.Collections.emptyList();
          bitField0_ = (bitField0_ & ~0x00000001);
        } else {
          scoresBuilder_.clear();
        }
        return this;
      }

      @java.lang.Override
      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return cs201game.protos.LeaderboardProto.internal_static_CS201Game_Leaderboard_descriptor;
      }

      @java.lang.Override
      public cs201game.protos.LeaderboardProto.Leaderboard getDefaultInstanceForType() {
        return cs201game.protos.LeaderboardProto.Leaderboard.getDefaultInstance();
      }

      @java.lang.Override
      public cs201game.protos.LeaderboardProto.Leaderboard build() {
        cs201game.protos.LeaderboardProto.Leaderboard result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      @java.lang.Override
      public cs201game.protos.LeaderboardProto.Leaderboard buildPartial() {
        cs201game.protos.LeaderboardProto.Leaderboard result = new cs201game.protos.LeaderboardProto.Leaderboard(this);
        int from_bitField0_ = bitField0_;
        if (scoresBuilder_ == null) {
          if (((bitField0_ & 0x00000001) != 0)) {
            scores_ = java.util.Collections.unmodifiableList(scores_);
            bitField0_ = (bitField0_ & ~0x00000001);
          }
          result.scores_ = scores_;
        } else {
          result.scores_ = scoresBuilder_.build();
        }
        onBuilt();
        return result;
      }

      @java.lang.Override
      public Builder clone() {
        return super.clone();
      }
      @java.lang.Override
      public Builder setField(
          com.google.protobuf.Descriptors.FieldDescriptor field,
          java.lang.Object value) {
        return super.setField(field, value);
      }
      @java.lang.Override
      public Builder clearField(
          com.google.protobuf.Descriptors.FieldDescriptor field) {
        return super.clearField(field);
      }
      @java.lang.Override
      public Builder clearOneof(
          com.google.protobuf.Descriptors.OneofDescriptor oneof) {
        return super.clearOneof(oneof);
      }
      @java.lang.Override
      public Builder setRepeatedField(
          com.google.protobuf.Descriptors.FieldDescriptor field,
          int index, java.lang.Object value) {
        return super.setRepeatedField(field, index, value);
      }
      @java.lang.Override
      public Builder addRepeatedField(
          com.google.protobuf.Descriptors.FieldDescriptor field,
          java.lang.Object value) {
        return super.addRepeatedField(field, value);
      }
      @java.lang.Override
      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof cs201game.protos.LeaderboardProto.Leaderboard) {
          return mergeFrom((cs201game.protos.LeaderboardProto.Leaderboard)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(cs201game.protos.LeaderboardProto.Leaderboard other) {
        if (other == cs201game.protos.LeaderboardProto.Leaderboard.getDefaultInstance()) return this;
        if (scoresBuilder_ == null) {
          if (!other.scores_.isEmpty()) {
            if (scores_.isEmpty()) {
              scores_ = other.scores_;
              bitField0_ = (bitField0_ & ~0x00000001);
            } else {
              ensureScoresIsMutable();
              scores_.addAll(other.scores_);
            }
            onChanged();
          }
        } else {
          if (!other.scores_.isEmpty()) {
            if (scoresBuilder_.isEmpty()) {
              scoresBuilder_.dispose();
              scoresBuilder_ = null;
              scores_ = other.scores_;
              bitField0_ = (bitField0_ & ~0x00000001);
              scoresBuilder_ = 
                com.google.protobuf.GeneratedMessageV3.alwaysUseFieldBuilders ?
                   getScoresFieldBuilder() : null;
            } else {
              scoresBuilder_.addAllMessages(other.scores_);
            }
          }
        }
        this.mergeUnknownFields(other.unknownFields);
        onChanged();
        return this;
      }

      @java.lang.Override
      public final boolean isInitialized() {
        return true;
      }

      @java.lang.Override
      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        cs201game.protos.LeaderboardProto.Leaderboard parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (cs201game.protos.LeaderboardProto.Leaderboard) e.getUnfinishedMessage();
          throw e.unwrapIOException();
        } finally {
          if (parsedMessage != null) {
            mergeFrom(parsedMessage);
          }
        }
        return this;
      }
      private int bitField0_;

      private java.util.List<cs201game.protos.PlayerScoreProto.PlayerScore> scores_ =
        java.util.Collections.emptyList();
      private void ensureScoresIsMutable() {
        if (!((bitField0_ & 0x00000001) != 0)) {
          scores_ = new java.util.ArrayList<cs201game.protos.PlayerScoreProto.PlayerScore>(scores_);
          bitField0_ |= 0x00000001;
         }
      }

      private com.google.protobuf.RepeatedFieldBuilderV3<
          cs201game.protos.PlayerScoreProto.PlayerScore, cs201game.protos.PlayerScoreProto.PlayerScore.Builder, cs201game.protos.PlayerScoreProto.PlayerScoreOrBuilder> scoresBuilder_;

      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public java.util.List<cs201game.protos.PlayerScoreProto.PlayerScore> getScoresList() {
        if (scoresBuilder_ == null) {
          return java.util.Collections.unmodifiableList(scores_);
        } else {
          return scoresBuilder_.getMessageList();
        }
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public int getScoresCount() {
        if (scoresBuilder_ == null) {
          return scores_.size();
        } else {
          return scoresBuilder_.getCount();
        }
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public cs201game.protos.PlayerScoreProto.PlayerScore getScores(int index) {
        if (scoresBuilder_ == null) {
          return scores_.get(index);
        } else {
          return scoresBuilder_.getMessage(index);
        }
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public Builder setScores(
          int index, cs201game.protos.PlayerScoreProto.PlayerScore value) {
        if (scoresBuilder_ == null) {
          if (value == null) {
            throw new NullPointerException();
          }
          ensureScoresIsMutable();
          scores_.set(index, value);
          onChanged();
        } else {
          scoresBuilder_.setMessage(index, value);
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public Builder setScores(
          int index, cs201game.protos.PlayerScoreProto.PlayerScore.Builder builderForValue) {
        if (scoresBuilder_ == null) {
          ensureScoresIsMutable();
          scores_.set(index, builderForValue.build());
          onChanged();
        } else {
          scoresBuilder_.setMessage(index, builderForValue.build());
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public Builder addScores(cs201game.protos.PlayerScoreProto.PlayerScore value) {
        if (scoresBuilder_ == null) {
          if (value == null) {
            throw new NullPointerException();
          }
          ensureScoresIsMutable();
          scores_.add(value);
          onChanged();
        } else {
          scoresBuilder_.addMessage(value);
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public Builder addScores(
          int index, cs201game.protos.PlayerScoreProto.PlayerScore value) {
        if (scoresBuilder_ == null) {
          if (value == null) {
            throw new NullPointerException();
          }
          ensureScoresIsMutable();
          scores_.add(index, value);
          onChanged();
        } else {
          scoresBuilder_.addMessage(index, value);
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public Builder addScores(
          cs201game.protos.PlayerScoreProto.PlayerScore.Builder builderForValue) {
        if (scoresBuilder_ == null) {
          ensureScoresIsMutable();
          scores_.add(builderForValue.build());
          onChanged();
        } else {
          scoresBuilder_.addMessage(builderForValue.build());
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public Builder addScores(
          int index, cs201game.protos.PlayerScoreProto.PlayerScore.Builder builderForValue) {
        if (scoresBuilder_ == null) {
          ensureScoresIsMutable();
          scores_.add(index, builderForValue.build());
          onChanged();
        } else {
          scoresBuilder_.addMessage(index, builderForValue.build());
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public Builder addAllScores(
          java.lang.Iterable<? extends cs201game.protos.PlayerScoreProto.PlayerScore> values) {
        if (scoresBuilder_ == null) {
          ensureScoresIsMutable();
          com.google.protobuf.AbstractMessageLite.Builder.addAll(
              values, scores_);
          onChanged();
        } else {
          scoresBuilder_.addAllMessages(values);
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public Builder clearScores() {
        if (scoresBuilder_ == null) {
          scores_ = java.util.Collections.emptyList();
          bitField0_ = (bitField0_ & ~0x00000001);
          onChanged();
        } else {
          scoresBuilder_.clear();
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public Builder removeScores(int index) {
        if (scoresBuilder_ == null) {
          ensureScoresIsMutable();
          scores_.remove(index);
          onChanged();
        } else {
          scoresBuilder_.remove(index);
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public cs201game.protos.PlayerScoreProto.PlayerScore.Builder getScoresBuilder(
          int index) {
        return getScoresFieldBuilder().getBuilder(index);
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public cs201game.protos.PlayerScoreProto.PlayerScoreOrBuilder getScoresOrBuilder(
          int index) {
        if (scoresBuilder_ == null) {
          return scores_.get(index);  } else {
          return scoresBuilder_.getMessageOrBuilder(index);
        }
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public java.util.List<? extends cs201game.protos.PlayerScoreProto.PlayerScoreOrBuilder> 
           getScoresOrBuilderList() {
        if (scoresBuilder_ != null) {
          return scoresBuilder_.getMessageOrBuilderList();
        } else {
          return java.util.Collections.unmodifiableList(scores_);
        }
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public cs201game.protos.PlayerScoreProto.PlayerScore.Builder addScoresBuilder() {
        return getScoresFieldBuilder().addBuilder(
            cs201game.protos.PlayerScoreProto.PlayerScore.getDefaultInstance());
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public cs201game.protos.PlayerScoreProto.PlayerScore.Builder addScoresBuilder(
          int index) {
        return getScoresFieldBuilder().addBuilder(
            index, cs201game.protos.PlayerScoreProto.PlayerScore.getDefaultInstance());
      }
      /**
       * <code>repeated .CS201Game.PlayerScore scores = 1;</code>
       */
      public java.util.List<cs201game.protos.PlayerScoreProto.PlayerScore.Builder> 
           getScoresBuilderList() {
        return getScoresFieldBuilder().getBuilderList();
      }
      private com.google.protobuf.RepeatedFieldBuilderV3<
          cs201game.protos.PlayerScoreProto.PlayerScore, cs201game.protos.PlayerScoreProto.PlayerScore.Builder, cs201game.protos.PlayerScoreProto.PlayerScoreOrBuilder> 
          getScoresFieldBuilder() {
        if (scoresBuilder_ == null) {
          scoresBuilder_ = new com.google.protobuf.RepeatedFieldBuilderV3<
              cs201game.protos.PlayerScoreProto.PlayerScore, cs201game.protos.PlayerScoreProto.PlayerScore.Builder, cs201game.protos.PlayerScoreProto.PlayerScoreOrBuilder>(
                  scores_,
                  ((bitField0_ & 0x00000001) != 0),
                  getParentForChildren(),
                  isClean());
          scores_ = null;
        }
        return scoresBuilder_;
      }
      @java.lang.Override
      public final Builder setUnknownFields(
          final com.google.protobuf.UnknownFieldSet unknownFields) {
        return super.setUnknownFields(unknownFields);
      }

      @java.lang.Override
      public final Builder mergeUnknownFields(
          final com.google.protobuf.UnknownFieldSet unknownFields) {
        return super.mergeUnknownFields(unknownFields);
      }


      // @@protoc_insertion_point(builder_scope:CS201Game.Leaderboard)
    }

    // @@protoc_insertion_point(class_scope:CS201Game.Leaderboard)
    private static final cs201game.protos.LeaderboardProto.Leaderboard DEFAULT_INSTANCE;
    static {
      DEFAULT_INSTANCE = new cs201game.protos.LeaderboardProto.Leaderboard();
    }

    public static cs201game.protos.LeaderboardProto.Leaderboard getDefaultInstance() {
      return DEFAULT_INSTANCE;
    }

    private static final com.google.protobuf.Parser<Leaderboard>
        PARSER = new com.google.protobuf.AbstractParser<Leaderboard>() {
      @java.lang.Override
      public Leaderboard parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new Leaderboard(input, extensionRegistry);
      }
    };

    public static com.google.protobuf.Parser<Leaderboard> parser() {
      return PARSER;
    }

    @java.lang.Override
    public com.google.protobuf.Parser<Leaderboard> getParserForType() {
      return PARSER;
    }

    @java.lang.Override
    public cs201game.protos.LeaderboardProto.Leaderboard getDefaultInstanceForType() {
      return DEFAULT_INSTANCE;
    }

  }

  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_CS201Game_Leaderboard_descriptor;
  private static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_CS201Game_Leaderboard_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static  com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\021leaderboard.proto\022\tCS201Game\032\022player_s" +
      "core.proto\"5\n\013Leaderboard\022&\n\006scores\030\001 \003(" +
      "\0132\026.CS201Game.PlayerScoreB-\n\020cs201game.p" +
      "rotosB\020LeaderboardProto\252\002\006Protosb\006proto3"
    };
    descriptor = com.google.protobuf.Descriptors.FileDescriptor
      .internalBuildGeneratedFileFrom(descriptorData,
        new com.google.protobuf.Descriptors.FileDescriptor[] {
          cs201game.protos.PlayerScoreProto.getDescriptor(),
        });
    internal_static_CS201Game_Leaderboard_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_CS201Game_Leaderboard_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_CS201Game_Leaderboard_descriptor,
        new java.lang.String[] { "Scores", });
    cs201game.protos.PlayerScoreProto.getDescriptor();
  }

  // @@protoc_insertion_point(outer_class_scope)
}
