classdef DynamicsRegressorParametersList < SwigRef
  methods
    function this = swig_this(self)
      this = iDynTreeMEX(3, self);
    end
    function varargout = parameters(self, varargin)
      narginchk(1, 2)
      if nargin==1
        nargoutchk(0, 1)
        varargout{1} = iDynTreeMEX(1568, self);
      else
        nargoutchk(0, 0)
        iDynTreeMEX(1569, self, varargin{1});
      end
    end
    function varargout = getDescriptionOfParameter(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1570, self, varargin{:});
    end
    function varargout = addParam(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1571, self, varargin{:});
    end
    function varargout = addList(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1572, self, varargin{:});
    end
    function varargout = findParam(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1573, self, varargin{:});
    end
    function varargout = getNrOfParameters(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1574, self, varargin{:});
    end
    function self = DynamicsRegressorParametersList(varargin)
      if nargin==1 && strcmp(class(varargin{1}),'SwigRef')
        if ~isnull(varargin{1})
          self.swigPtr = varargin{1}.swigPtr;
        end
      else
        tmp = iDynTreeMEX(1575, varargin{:});
        self.swigPtr = tmp.swigPtr;
        tmp.swigPtr = [];
      end
    end
    function delete(self)
      if self.swigPtr
        iDynTreeMEX(1576, self);
        self.swigPtr=[];
      end
    end
  end
  methods(Static)
  end
end
