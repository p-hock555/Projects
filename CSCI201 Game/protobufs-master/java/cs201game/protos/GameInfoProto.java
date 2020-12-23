// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: game_info.proto

package cs201game.protos;

public final class GameInfoProto {
  private GameInfoProto() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }

  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
    registerAllExtensions(
        (com.google.protobuf.ExtensionRegistryLite) registry);
  }
  public interface GameInfoOrBuilder extends
      // @@protoc_insertion_point(interface_extends:CS201Game.GameInfo)
      com.google.protobuf.MessageOrBuilder {

    /**
     * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
     */
    java.util.List<cs201game.protos.PlayerInfoProto.PlayerInfo> 
        getPlayersList();
    /**
     * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
     */
    cs201game.protos.PlayerInfoProto.PlayerInfo getPlayers(int index);
    /**
     * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
     */
    int getPlayersCount();
    /**
     * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
     */
    java.util.List<? extends cs201game.protos.PlayerInfoProto.PlayerInfoOrBuilder> 
        getPlayersOrBuilderList();
    /**
     * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
     */
    cs201game.protos.PlayerInfoProto.PlayerInfoOrBuilder getPlayersOrBuilder(
        int index);
  }
  /**
   * Protobuf type {@code CS201Game.GameInfo}
   */
  public static final class GameInfo extends
      com.google.protobuf.GeneratedMessageV3 implements
      // @@protoc_insertion_point(message_implements:CS201Game.GameInfo)
      GameInfoOrBuilder {
  private static final long serialVersionUID = 0L;
    // Use GameInfo.newBuilder() to construct.
    private GameInfo(com.google.protobuf.GeneratedMessageV3.Builder<?> builder) {
      super(builder);
    }
    private GameInfo() {
      players_ = java.util.Collections.emptyList();
    }

    @java.lang.Override
    @SuppressWarnings({"unused"})
    protected java.lang.Object newInstance(
        UnusedPrivateParameter unused) {
      return new GameInfo();
    }

    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
    getUnknownFields() {
      return this.unknownFields;
    }
    private GameInfo(
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
                players_ = new java.util.ArrayList<cs201game.protos.PlayerInfoProto.PlayerInfo>();
                mutable_bitField0_ |= 0x00000001;
              }
              players_.add(
                  input.readMessage(cs201game.protos.PlayerInfoProto.PlayerInfo.parser(), extensionRegistry));
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
          players_ = java.util.Collections.unmodifiableList(players_);
        }
        this.unknownFields = unknownFields.build();
        makeExtensionsImmutable();
      }
    }
    public static final com.google.protobuf.Descriptors.Descriptor
        getDescriptor() {
      return cs201game.protos.GameInfoProto.internal_static_CS201Game_GameInfo_descriptor;
    }

    @java.lang.Override
    protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return cs201game.protos.GameInfoProto.internal_static_CS201Game_GameInfo_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              cs201game.protos.GameInfoProto.GameInfo.class, cs201game.protos.GameInfoProto.GameInfo.Builder.class);
    }

    public static final int PLAYERS_FIELD_NUMBER = 1;
    private java.util.List<cs201game.protos.PlayerInfoProto.PlayerInfo> players_;
    /**
     * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
     */
    @java.lang.Override
    public java.util.List<cs201game.protos.PlayerInfoProto.PlayerInfo> getPlayersList() {
      return players_;
    }
    /**
     * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
     */
    @java.lang.Override
    public java.util.List<? extends cs201game.protos.PlayerInfoProto.PlayerInfoOrBuilder> 
        getPlayersOrBuilderList() {
      return players_;
    }
    /**
     * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
     */
    @java.lang.Override
    public int getPlayersCount() {
      return players_.size();
    }
    /**
     * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
     */
    @java.lang.Override
    public cs201game.protos.PlayerInfoProto.PlayerInfo getPlayers(int index) {
      return players_.get(index);
    }
    /**
     * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
     */
    @java.lang.Override
    public cs201game.protos.PlayerInfoProto.PlayerInfoOrBuilder getPlayersOrBuilder(
        int index) {
      return players_.get(index);
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
      for (int i = 0; i < players_.size(); i++) {
        output.writeMessage(1, players_.get(i));
      }
      unknownFields.writeTo(output);
    }

    @java.lang.Override
    public int getSerializedSize() {
      int size = memoizedSize;
      if (size != -1) return size;

      size = 0;
      for (int i = 0; i < players_.size(); i++) {
        size += com.google.protobuf.CodedOutputStream
          .computeMessageSize(1, players_.get(i));
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
      if (!(obj instanceof cs201game.protos.GameInfoProto.GameInfo)) {
        return super.equals(obj);
      }
      cs201game.protos.GameInfoProto.GameInfo other = (cs201game.protos.GameInfoProto.GameInfo) obj;

      if (!getPlayersList()
          .equals(other.getPlayersList())) return false;
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
      if (getPlayersCount() > 0) {
        hash = (37 * hash) + PLAYERS_FIELD_NUMBER;
        hash = (53 * hash) + getPlayersList().hashCode();
      }
      hash = (29 * hash) + unknownFields.hashCode();
      memoizedHashCode = hash;
      return hash;
    }

    public static cs201game.protos.GameInfoProto.GameInfo parseFrom(
        java.nio.ByteBuffer data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static cs201game.protos.GameInfoProto.GameInfo parseFrom(
        java.nio.ByteBuffer data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static cs201game.protos.GameInfoProto.GameInfo parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static cs201game.protos.GameInfoProto.GameInfo parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static cs201game.protos.GameInfoProto.GameInfo parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static cs201game.protos.GameInfoProto.GameInfo parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static cs201game.protos.GameInfoProto.GameInfo parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseWithIOException(PARSER, input);
    }
    public static cs201game.protos.GameInfoProto.GameInfo parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseWithIOException(PARSER, input, extensionRegistry);
    }
    public static cs201game.protos.GameInfoProto.GameInfo parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseDelimitedWithIOException(PARSER, input);
    }
    public static cs201game.protos.GameInfoProto.GameInfo parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseDelimitedWithIOException(PARSER, input, extensionRegistry);
    }
    public static cs201game.protos.GameInfoProto.GameInfo parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseWithIOException(PARSER, input);
    }
    public static cs201game.protos.GameInfoProto.GameInfo parseFrom(
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
    public static Builder newBuilder(cs201game.protos.GameInfoProto.GameInfo prototype) {
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
     * Protobuf type {@code CS201Game.GameInfo}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessageV3.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:CS201Game.GameInfo)
        cs201game.protos.GameInfoProto.GameInfoOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return cs201game.protos.GameInfoProto.internal_static_CS201Game_GameInfo_descriptor;
      }

      @java.lang.Override
      protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return cs201game.protos.GameInfoProto.internal_static_CS201Game_GameInfo_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                cs201game.protos.GameInfoProto.GameInfo.class, cs201game.protos.GameInfoProto.GameInfo.Builder.class);
      }

      // Construct using cs201game.protos.GameInfoProto.GameInfo.newBuilder()
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
          getPlayersFieldBuilder();
        }
      }
      @java.lang.Override
      public Builder clear() {
        super.clear();
        if (playersBuilder_ == null) {
          players_ = java.util.Collections.emptyList();
          bitField0_ = (bitField0_ & ~0x00000001);
        } else {
          playersBuilder_.clear();
        }
        return this;
      }

      @java.lang.Override
      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return cs201game.protos.GameInfoProto.internal_static_CS201Game_GameInfo_descriptor;
      }

      @java.lang.Override
      public cs201game.protos.GameInfoProto.GameInfo getDefaultInstanceForType() {
        return cs201game.protos.GameInfoProto.GameInfo.getDefaultInstance();
      }

      @java.lang.Override
      public cs201game.protos.GameInfoProto.GameInfo build() {
        cs201game.protos.GameInfoProto.GameInfo result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      @java.lang.Override
      public cs201game.protos.GameInfoProto.GameInfo buildPartial() {
        cs201game.protos.GameInfoProto.GameInfo result = new cs201game.protos.GameInfoProto.GameInfo(this);
        int from_bitField0_ = bitField0_;
        if (playersBuilder_ == null) {
          if (((bitField0_ & 0x00000001) != 0)) {
            players_ = java.util.Collections.unmodifiableList(players_);
            bitField0_ = (bitField0_ & ~0x00000001);
          }
          result.players_ = players_;
        } else {
          result.players_ = playersBuilder_.build();
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
        if (other instanceof cs201game.protos.GameInfoProto.GameInfo) {
          return mergeFrom((cs201game.protos.GameInfoProto.GameInfo)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(cs201game.protos.GameInfoProto.GameInfo other) {
        if (other == cs201game.protos.GameInfoProto.GameInfo.getDefaultInstance()) return this;
        if (playersBuilder_ == null) {
          if (!other.players_.isEmpty()) {
            if (players_.isEmpty()) {
              players_ = other.players_;
              bitField0_ = (bitField0_ & ~0x00000001);
            } else {
              ensurePlayersIsMutable();
              players_.addAll(other.players_);
            }
            onChanged();
          }
        } else {
          if (!other.players_.isEmpty()) {
            if (playersBuilder_.isEmpty()) {
              playersBuilder_.dispose();
              playersBuilder_ = null;
              players_ = other.players_;
              bitField0_ = (bitField0_ & ~0x00000001);
              playersBuilder_ = 
                com.google.protobuf.GeneratedMessageV3.alwaysUseFieldBuilders ?
                   getPlayersFieldBuilder() : null;
            } else {
              playersBuilder_.addAllMessages(other.players_);
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
        cs201game.protos.GameInfoProto.GameInfo parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (cs201game.protos.GameInfoProto.GameInfo) e.getUnfinishedMessage();
          throw e.unwrapIOException();
        } finally {
          if (parsedMessage != null) {
            mergeFrom(parsedMessage);
          }
        }
        return this;
      }
      private int bitField0_;

      private java.util.List<cs201game.protos.PlayerInfoProto.PlayerInfo> players_ =
        java.util.Collections.emptyList();
      private void ensurePlayersIsMutable() {
        if (!((bitField0_ & 0x00000001) != 0)) {
          players_ = new java.util.ArrayList<cs201game.protos.PlayerInfoProto.PlayerInfo>(players_);
          bitField0_ |= 0x00000001;
         }
      }

      private com.google.protobuf.RepeatedFieldBuilderV3<
          cs201game.protos.PlayerInfoProto.PlayerInfo, cs201game.protos.PlayerInfoProto.PlayerInfo.Builder, cs201game.protos.PlayerInfoProto.PlayerInfoOrBuilder> playersBuilder_;

      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public java.util.List<cs201game.protos.PlayerInfoProto.PlayerInfo> getPlayersList() {
        if (playersBuilder_ == null) {
          return java.util.Collections.unmodifiableList(players_);
        } else {
          return playersBuilder_.getMessageList();
        }
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public int getPlayersCount() {
        if (playersBuilder_ == null) {
          return players_.size();
        } else {
          return playersBuilder_.getCount();
        }
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public cs201game.protos.PlayerInfoProto.PlayerInfo getPlayers(int index) {
        if (playersBuilder_ == null) {
          return players_.get(index);
        } else {
          return playersBuilder_.getMessage(index);
        }
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public Builder setPlayers(
          int index, cs201game.protos.PlayerInfoProto.PlayerInfo value) {
        if (playersBuilder_ == null) {
          if (value == null) {
            throw new NullPointerException();
          }
          ensurePlayersIsMutable();
          players_.set(index, value);
          onChanged();
        } else {
          playersBuilder_.setMessage(index, value);
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public Builder setPlayers(
          int index, cs201game.protos.PlayerInfoProto.PlayerInfo.Builder builderForValue) {
        if (playersBuilder_ == null) {
          ensurePlayersIsMutable();
          players_.set(index, builderForValue.build());
          onChanged();
        } else {
          playersBuilder_.setMessage(index, builderForValue.build());
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public Builder addPlayers(cs201game.protos.PlayerInfoProto.PlayerInfo value) {
        if (playersBuilder_ == null) {
          if (value == null) {
            throw new NullPointerException();
          }
          ensurePlayersIsMutable();
          players_.add(value);
          onChanged();
        } else {
          playersBuilder_.addMessage(value);
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public Builder addPlayers(
          int index, cs201game.protos.PlayerInfoProto.PlayerInfo value) {
        if (playersBuilder_ == null) {
          if (value == null) {
            throw new NullPointerException();
          }
          ensurePlayersIsMutable();
          players_.add(index, value);
          onChanged();
        } else {
          playersBuilder_.addMessage(index, value);
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public Builder addPlayers(
          cs201game.protos.PlayerInfoProto.PlayerInfo.Builder builderForValue) {
        if (playersBuilder_ == null) {
          ensurePlayersIsMutable();
          players_.add(builderForValue.build());
          onChanged();
        } else {
          playersBuilder_.addMessage(builderForValue.build());
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public Builder addPlayers(
          int index, cs201game.protos.PlayerInfoProto.PlayerInfo.Builder builderForValue) {
        if (playersBuilder_ == null) {
          ensurePlayersIsMutable();
          players_.add(index, builderForValue.build());
          onChanged();
        } else {
          playersBuilder_.addMessage(index, builderForValue.build());
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public Builder addAllPlayers(
          java.lang.Iterable<? extends cs201game.protos.PlayerInfoProto.PlayerInfo> values) {
        if (playersBuilder_ == null) {
          ensurePlayersIsMutable();
          com.google.protobuf.AbstractMessageLite.Builder.addAll(
              values, players_);
          onChanged();
        } else {
          playersBuilder_.addAllMessages(values);
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public Builder clearPlayers() {
        if (playersBuilder_ == null) {
          players_ = java.util.Collections.emptyList();
          bitField0_ = (bitField0_ & ~0x00000001);
          onChanged();
        } else {
          playersBuilder_.clear();
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public Builder removePlayers(int index) {
        if (playersBuilder_ == null) {
          ensurePlayersIsMutable();
          players_.remove(index);
          onChanged();
        } else {
          playersBuilder_.remove(index);
        }
        return this;
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public cs201game.protos.PlayerInfoProto.PlayerInfo.Builder getPlayersBuilder(
          int index) {
        return getPlayersFieldBuilder().getBuilder(index);
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public cs201game.protos.PlayerInfoProto.PlayerInfoOrBuilder getPlayersOrBuilder(
          int index) {
        if (playersBuilder_ == null) {
          return players_.get(index);  } else {
          return playersBuilder_.getMessageOrBuilder(index);
        }
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public java.util.List<? extends cs201game.protos.PlayerInfoProto.PlayerInfoOrBuilder> 
           getPlayersOrBuilderList() {
        if (playersBuilder_ != null) {
          return playersBuilder_.getMessageOrBuilderList();
        } else {
          return java.util.Collections.unmodifiableList(players_);
        }
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public cs201game.protos.PlayerInfoProto.PlayerInfo.Builder addPlayersBuilder() {
        return getPlayersFieldBuilder().addBuilder(
            cs201game.protos.PlayerInfoProto.PlayerInfo.getDefaultInstance());
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public cs201game.protos.PlayerInfoProto.PlayerInfo.Builder addPlayersBuilder(
          int index) {
        return getPlayersFieldBuilder().addBuilder(
            index, cs201game.protos.PlayerInfoProto.PlayerInfo.getDefaultInstance());
      }
      /**
       * <code>repeated .CS201Game.PlayerInfo players = 1;</code>
       */
      public java.util.List<cs201game.protos.PlayerInfoProto.PlayerInfo.Builder> 
           getPlayersBuilderList() {
        return getPlayersFieldBuilder().getBuilderList();
      }
      private com.google.protobuf.RepeatedFieldBuilderV3<
          cs201game.protos.PlayerInfoProto.PlayerInfo, cs201game.protos.PlayerInfoProto.PlayerInfo.Builder, cs201game.protos.PlayerInfoProto.PlayerInfoOrBuilder> 
          getPlayersFieldBuilder() {
        if (playersBuilder_ == null) {
          playersBuilder_ = new com.google.protobuf.RepeatedFieldBuilderV3<
              cs201game.protos.PlayerInfoProto.PlayerInfo, cs201game.protos.PlayerInfoProto.PlayerInfo.Builder, cs201game.protos.PlayerInfoProto.PlayerInfoOrBuilder>(
                  players_,
                  ((bitField0_ & 0x00000001) != 0),
                  getParentForChildren(),
                  isClean());
          players_ = null;
        }
        return playersBuilder_;
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


      // @@protoc_insertion_point(builder_scope:CS201Game.GameInfo)
    }

    // @@protoc_insertion_point(class_scope:CS201Game.GameInfo)
    private static final cs201game.protos.GameInfoProto.GameInfo DEFAULT_INSTANCE;
    static {
      DEFAULT_INSTANCE = new cs201game.protos.GameInfoProto.GameInfo();
    }

    public static cs201game.protos.GameInfoProto.GameInfo getDefaultInstance() {
      return DEFAULT_INSTANCE;
    }

    private static final com.google.protobuf.Parser<GameInfo>
        PARSER = new com.google.protobuf.AbstractParser<GameInfo>() {
      @java.lang.Override
      public GameInfo parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new GameInfo(input, extensionRegistry);
      }
    };

    public static com.google.protobuf.Parser<GameInfo> parser() {
      return PARSER;
    }

    @java.lang.Override
    public com.google.protobuf.Parser<GameInfo> getParserForType() {
      return PARSER;
    }

    @java.lang.Override
    public cs201game.protos.GameInfoProto.GameInfo getDefaultInstanceForType() {
      return DEFAULT_INSTANCE;
    }

  }

  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_CS201Game_GameInfo_descriptor;
  private static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_CS201Game_GameInfo_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static  com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\017game_info.proto\022\tCS201Game\032\021player_inf" +
      "o.proto\"2\n\010GameInfo\022&\n\007players\030\001 \003(\0132\025.C" +
      "S201Game.PlayerInfoB*\n\020cs201game.protosB" +
      "\rGameInfoProto\252\002\006Protosb\006proto3"
    };
    descriptor = com.google.protobuf.Descriptors.FileDescriptor
      .internalBuildGeneratedFileFrom(descriptorData,
        new com.google.protobuf.Descriptors.FileDescriptor[] {
          cs201game.protos.PlayerInfoProto.getDescriptor(),
        });
    internal_static_CS201Game_GameInfo_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_CS201Game_GameInfo_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_CS201Game_GameInfo_descriptor,
        new java.lang.String[] { "Players", });
    cs201game.protos.PlayerInfoProto.getDescriptor();
  }

  // @@protoc_insertion_point(outer_class_scope)
}